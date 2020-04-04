#include <ST7036.h>
#include <LCD_C0220BiZ.h>
#include <lcd.h>
#include <SPI.h>
#include <SRAM_23LC.h>
#include <Encoder.h>

#define DOUBLE_CLICK_TIME 1000

volatile uint8_t adcCount = 0;
volatile uint16_t adcMeas = 0;
ISR(ADC_vect) {
    adcCount++;
    adcMeas += ADCH;
    ADCSRA &= !(1 << ADIF); // Do we need to manually clear the interrupt flag?
}

static inline uint8_t getADC() {
	// Get average over last sample period
    uint8_t retVal = (adcMeas / adcCount);
    adcCount = 0;
    adcMeas = 0;
    return retVal; // Returns 0 in the case of no valid data
}

class MotorDriver {
private:
	Encoder motorEncoder = Encoder(10, 9); // Initialize motor encoder
	SRAM_23LC sram = SRAM_23LC(&SPI, 8, SRAM_23LCV512); // Initialize SRAM on SPI as 512kbit

	int32_t targetSpeed; // Input from main program (expressed in 63rds of position per sample time)
	int32_t targetPosition; // Integral of targetSpeed

	typedef struct {
		uint8_t kp;
		uint8_t kd;
		uint8_t ki;
	} pidGain_t;

	const pidGain_t posGain = { 2, 6, 10 }; // These values are fractions of 256
	const pidGain_t curGain = { 1, 10, 1 }; // This is due to a right-shift in the code

	int16_t posIntegral = 0; // Left these outside of pidStep to allow resetting of integral windup
	int16_t curIntegral = 0;

    // Model step function
    void pidStep() {
		if (adcCount == 0)
			return; // If we don't have new data we can't do anything

		// Disable interrupts and determine the time since last step
		uint8_t s = SREG;
		cli();
		uint8_t timeStep = adcCount;
		uint8_t currentMeasurement = getADC();
		SREG = s;

		// Use position error to determine approperiate current
		static int16_t prevPosError = 0; // For derivative
        int16_t posError = targetPosition - motorEncoder.read(); // Calculate error
		int16_t posProportional = posError * posGain.kp; // Calculate proportional response
		posIntegral += posError * posGain.ki * timeStep; // Calculate integral response
		int16_t posDerivative = ((posError - prevPosError) * posGain.kd) / timeStep; // Calculate derivative response
		int16_t desiredCurrent = posProportional + posIntegral + posDerivative; // Sum responses
		prevPosError = posError; // Save this error for next iteration
		desiredCurrent >>= 6; // Divide by 64
		// Limit the desired current to acceptable limits
		// This will prevent fault conditions from occurring, theoretically
		// This also prevents current-limits at the driver from causing integral windup
		if (desiredCurrent > 100)
			desiredCurrent = 100;
		else if (desiredCurrent < -100)
			desiredCurrent = -100;

		static int16_t prevCurError = 0; // For derivative
		int16_t curError = desiredCurrent - currentMeasurement; // Calculate error
		int16_t curProportional = curError * curGain.kp; // Calculate proportional response
		curIntegral += curError * curGain.ki * timeStep; // Calculate integral response
		int16_t curDerivative = ((curError - prevCurError) * curGain.kd) / timeStep; // Calculate derivative reponse
		int16_t desiredDuty = curProportional + curIntegral + curDerivative; // Sum responses
		prevCurError = curError; // Save this error for next iteration

		if (desiredDuty >= 0) {
			OCR1AL = 0xFF - (desiredDuty >> 7); // Scale down to 8-bit
			OCR1BL = 0xFF; // Output is 0
		}
		else {
			OCR1AL = 0xFF; // Output is 0
			OCR1BL = 0xFF - ((-desiredDuty - 1) >> 7); // Scale down to 8-bit
		}
    }

	void integrateSpeed() { // This calculates an integral using only integers
		const static int8_t integratorDivisor = 63;
		static int8_t integratorFraction = 0;
		integratorFraction += targetSpeed % integratorDivisor;
		if (integratorFraction >= integratorDivisor) {
			integratorFraction -= integratorDivisor;
			targetPosition += (targetSpeed / integratorDivisor) + 1;
		}
		else if (integratorFraction <= -integratorDivisor) {
			integratorFraction += integratorDivisor;
			targetPosition += (targetSpeed / integratorDivisor) - 1;
		}
		else
			targetPosition += (targetSpeed / integratorDivisor);
	}
public:
	MotorDriver() {
		sram.begin(); // I hope this is allowed to be called in this constructor
		// Write last known position to encoder
		motorEncoder.write((int32_t)sram.readByte(0x0000));

		// TC1 setup as follows:
		//     COM1A to 11 (inverting PWM mode) overrides GPIO output value
		//     COM1B to 11 (inverting PWM mode) overrides GPIO output value
		//     WGM1 to 0101 (fast 8-bit PWM)
		//     CS1 to 001 (no prescaling)
		// This results in 62.5kHz 8-bit dual-channel PWM suitable for signalling DRV887x drivers
		// It should be noted that Timer0 is always running with 64 prescale in Arduino core
		TCCR1A = (1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0) | (1 << WGM10);
		TCCR1B = (1 << WGM12) | (1 << CS10);
		OCR1AL = 0xFF; // Initialize channel A to MAX (causes a DC low state)
		OCR1BL = 0xFF; // Initialize channel B to MAX (causes a DC low state)
		DDRB |= (1 << PINB1) | (1 << PINB2); // PB1 and PB2 to output

		// ADC setup as follows:
		//     ADTS to 100 (trigger on Timer0 overflow every 1.024ms)
		//     ADC7D (missing from iom328pb.h for integrated variant) is set to disable digital buffer on ADC7
		//     ADLAR to 1 to right-adjust results into ADCH
		//     MUX to 111 to use channel 7
		//     ADATE to 1 to use auto-triggering
		//     ADPS to 111 to use 128 prescale
		//     ADEN to 1 to enable the ADC
		//     ADSC to 1 to immediately start converting (and continue indefinitely
        //     ADIE to 1 to enable the ADC ISR
		ADCSRB = (1 << ADTS2);
#ifdef __AVR_atmega328pb__
		DIDR0 = 0x80;
#endif
		ADMUX = (1 << ADLAR) | (7 << MUX0);
        uint8_t s = SREG;
        cli();
		ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADATE) | (1 << ADIE) | (7 << ADPS0);
        SREG = s;

		targetPosition = motorEncoder.read();
	}

	void step() {
		if (ADCSRA & (1 << ADIF)) { // if current reading is available do the stuff, otherwise just return
			ADCSRA &= !(1 << ADIF); // clear data available flag
			integrateSpeed(); // Update targetPosition for this step
			pidStep(); // Update the motor outputs
#ifdef __AVR_atmega328pb__
			saveState();
#endif
		}
	}

	void saveState() {
		sram.writeByte(0x0000, motorEncoder.read()); // In case we lose power
	}

	void stop() {
		setSpeed(0); // Make sure we aren't changing our target
		targetPosition = motorEncoder.read(); // Make sure our new target is where we already are
		posIntegral = 0; // Reset internal control integrals so we don't see windup effect
		curIntegral = 0;
	}

	void setSpeed(int32_t target) {
		targetSpeed = target;
	}

	void incSpeed() {
		setSpeed(targetSpeed + 1);
	}

	void decSpeed() {
		setSpeed(targetSpeed - 1);
	}

	uint32_t getPos() {
		return motorEncoder.read();
	}

	int16_t getCurIntegralMag() {
		if (curIntegral < 0)
			return -curIntegral;
		else
			return curIntegral;
	}

    void calibrate() {
        motorEncoder.write(0);
        sram.writeByte(0x0000, 0);
    }
};

class LEDdriver {
private:
	typedef struct backlight {
		uint8_t red, green, blue;
	} backlight_t;

	typedef struct ledstate {
		uint8_t fill;
		uint8_t feed;
		uint8_t inc;
		uint8_t dec;
		uint8_t stop;
		backlight_t lcd;
	} ledstate_t;

	ledstate_t ledstate = { LOW, LOW, LOW, LOW, LOW, { LOW, LOW, LOW } };

public:
	LEDdriver() {
		PORTE &= ~(1 << DDRE0);
		DDRE |= (1 << DDRE0);
	}
	void writeFill(uint8_t fill_val) {
		ledstate.fill = fill_val;
	}
	void writeFeed(uint8_t feed_val) {
		ledstate.feed = feed_val;
	}
	void writeInc(uint8_t inc_val) {
		ledstate.inc = inc_val;
	}
	void writeDec(uint8_t dec_val) {
		ledstate.dec = dec_val;
	}
	void writeStop(uint8_t stop_val) {
		ledstate.stop = stop_val;
	}
	void writeRed(uint8_t red_val) {
		ledstate.lcd.red = red_val;
	}
	void writeGreen(uint8_t green_val) {
		ledstate.lcd.green = green_val;
	}
	void writeBlue(uint8_t blue_val) {
		ledstate.lcd.blue = blue_val;
	}

	void update() {
		uint8_t updated_data = 0;
		// Sending the LED values as fast as possible
		SPI.beginTransaction(SPISettings(8000000, LSBFIRST, SPI_MODE0));
		updated_data |= ledstate.stop;
		updated_data |= (ledstate.inc << 1);
		updated_data |= (ledstate.dec << 2);
		updated_data |= (ledstate.feed << 3);
		updated_data |= (ledstate.fill << 4);
		updated_data |= (ledstate.lcd.red << 5);
		updated_data |= (ledstate.lcd.green << 6);
		updated_data |= (ledstate.lcd.blue << 7);
		SPI.transfer(updated_data);
		SPI.transfer(0x00);
		SPI.endTransaction();
		PORTE |= ~(1 << PORTE0);
		PORTE &= ~(1 << PORTE0);
	}
};

class Button {
private:
	uint8_t pin; // Pin we are monitoring
	uint8_t state; // Debounced state of pin
	uint8_t debouncing; // Indicates we are debouncing
	uint8_t debounce_delay; // Desired debounce delay in ms
	unsigned long debounce_start; // When we started the debounce
	unsigned long old_debounce_start; // Previous value of debounce_start
public:
	Button(uint8_t in, uint8_t del) {
		pin = in; // Initialize the pin variable
		debounce_delay = del; // Initialize the desired debounce delay
		debouncing = 0; // Don't debounce at start
		pinMode(pin, INPUT_PULLUP); // No press is HIGH input
		state = digitalRead(pin); // Initialize with whatever state is on pin
	}

	void step(unsigned long time) {
		if (debouncing) {
			if ((time - debounce_start) >= debounce_delay) {
				debouncing = 0;
			}
		}
		if (!debouncing) {
			uint8_t pinval = digitalRead(pin);
			if (state != pinval) {
				debouncing = 1; // We detected a change and need to start debouncing
				state = pinval; // Update the state immediately
				old_debounce_start = debounce_start; // Save the old value
				debounce_start = time; // Set the new timer reference
			}
		}
	}

	uint8_t getState() {
		return state;
	}

	unsigned long getClickDelta() {
		return debounce_start - old_debounce_start;
	}
};

Button fill(4, 25); // Create button drivers that handle debounce and double-click functionality
Button feed(14, 25);
Button speed_inc(16, 25);
Button speed_dec(17, 25);
Button stop(15, 25);

MotorDriver motor; // Create the MotorDriver object

LCD_C0220BIZ display; // Create the LCD object

LEDdriver leds; // Create the LED object

void setup()
{
	SPI.begin(); // Initialize SPI
	Serial.begin(9600); // Because why not
	display.init(); // Initialize display
	DDRE |= (1 << DDRE1); // Buzzer is output
}

typedef enum direction {
	STOPPED = 0,
	FILLING,
	DISPENSING
} direction_t;

typedef enum mode {
	MANUAL = 0,
	AUTO
} mode_t;

typedef enum fault {
	NONE = 0,
	STALLED
} fault_t;

typedef struct timer {
	uint8_t ten_minutes;
	uint8_t one_minutes;
	uint8_t ten_seconds;
	uint8_t one_seconds;
} timer_t;

void loop() {
	static int16_t user_speed = 1; // Speed that the user wants
	static direction_t direction = STOPPED; // Current desired motor direction
	static mode_t mode = MANUAL; // Current locomotion mode
	static uint32_t last_lcd_update = 0; // Time of last LCD update to make sure we don't waste time on it
	static fault_t fault_status = NONE; // Keep track of fault status
	static uint32_t buzzerStart = 0; // To limit buzzer loudness
	static uint8_t buzzing = 0; // Buzzer status

	// Update motor internal tickery
	if (fault_status == STALLED) {
		user_speed = 1;
	}
	if (direction == FILLING)
		motor.setSpeed(user_speed);
	else if (direction == DISPENSING)
		motor.setSpeed(-user_speed);
	else
		motor.stop();
	motor.step();

	// Update button internal tickery
	unsigned long curTime = millis();
	fill.step(curTime);
	feed.step(curTime);
	speed_inc.step(curTime);
	speed_dec.step(curTime);
	stop.step(curTime);

	// Motor fault detection is tripped when the integral portion of the
	// current control blows way out of proportion. Device will reverse
	// at the lowest speed setting and remain in that state until the
	// magnitude of the integral goes below 10% of the trip limit
	// Also calibrate if we hit the feed end stop and just stop if
	// we hit the fill limit.
	if (motor.getCurIntegralMag() > 10000) {
		if (PORTD & (1 << PORTD7) != 0) {
			motor.stop();
			motor.calibrate();
		}
		else if (PORTD & (1 << PORTD6) != 0) {
			motor.stop();
		}
		else {
			if (fault_status != STALLED)
				direction = ((direction == FILLING) ? DISPENSING : FILLING);
			fault_status = STALLED;
		}
	}
	else if (motor.getCurIntegralMag() < 1000)
		fault_status = NONE;

#ifdef __AVR_atmega328pb__
	if (PORTD & ((1 << PORTD7) | (1 << PORTD6)) != 0) {
		if (buzzing == 0) {
			buzzerStart = millis();
			buzzing = 1;
			PORTE |= (1 << PORTE1);
		}
		else if (millis() - buzzerStart > 350) {
			buzzing = 2;
			PORTE &= ~(1 << PORTE1);
		}
	}
#endif

	if (stop.getState() == 0) {
		direction = STOPPED;
	}
	else {
		if (fill.getState() == 0) {
			direction = DISPENSING; // Dispensing food (direction is negative)
			if (fill.getClickDelta() < DOUBLE_CLICK_TIME)
				mode = AUTO;
			else
				mode = MANUAL;
		}
		else if (fill.getState() == 1) {
			if (mode == MANUAL)
				direction = STOPPED;
		}

		if (feed.getState() == 0) {
			direction = FILLING; // Filling food (direction is positive)
			if (feed.getClickDelta() < DOUBLE_CLICK_TIME)
				mode = AUTO;
			else
				mode = MANUAL;
		}
		else if (feed.getState() == 1) {
			if (mode == MANUAL)
				direction = STOPPED;
		}

		if (speed_inc.getState() == 0) {
			if(user_speed < 32767)
				user_speed++;
			leds.writeInc(HIGH);
		}
		else {
			leds.writeInc(LOW);
		}

		if (speed_dec.getState() == 0) {
			if(user_speed > 1)
				user_speed--;
			leds.writeDec(HIGH);
		}
		else{
			leds.writeDec(LOW);
	}

	if (fault_status == STALLED) {
		leds.writeStop(HIGH);
		leds.writeFeed(HIGH);
		leds.writeFill(HIGH);
		leds.writeBlue(LOW);
		leds.writeRed(HIGH);
		leds.writeGreen(LOW);
	}
	else if (direction == STOPPED) {
		leds.writeStop(HIGH);
		leds.writeFeed(LOW);
		leds.writeFill(LOW);
		leds.writeBlue(HIGH);
		leds.writeRed(HIGH);
		leds.writeGreen(HIGH);
	}
	else {
		if (direction == FILLING) {
			leds.writeFill(HIGH);
			leds.writeFeed(LOW);
		}
		else {
			leds.writeFeed(HIGH);
			leds.writeFill(LOW);
		}
		leds.writeStop(LOW);
		leds.writeBlue(HIGH);
		leds.writeRed(HIGH);
		leds.writeGreen(HIGH);
	}

	// Updating the display (200ms means 5Hz update rate, close to the limit of the module)
	if ((millis() - last_lcd_update) > 200) {
		display.home(); // Return cursor to top left
		motor.saveState(); // Save state of the motor just in case it is disabled in driver
		leds.update(); // Update LED status

		// The following sets up the 6 possible display conditions
		char topbuffer[17];
		char botbuffer[17];
		if (fault_status == STALLED) {
			strcpy(topbuffer, "  Motor fault   ");
			strcpy(botbuffer, "  Service unit  ");
		}
		else {
			char time[6];
			strcpy(topbuffer, "Time: ");

			// This calculates time remaining using the desired speed and the current position
			int32_t time_remaining = motor.getPos() / user_speed * 2 / 31; // There are 15.5*user_speed encoder steps per second
			if (time_remaining < 0)
				time_remaining = 0;

			// Now calculate all the numbers and add 0x30 to make them ASCII
			time[0] = (time_remaining / 600) + 0x30;
			time[1] = ((time_remaining % 600) / 60) + 0x30;
			time[2] = ':';
			time[3] = ((time_remaining % 60) / 10) + 0x30;
			time[4] = (time_remaining % 10) + 0x30;
			time[5] = 0;

			strcat(topbuffer, time);

			if (mode == MANUAL)
				strcat(topbuffer, " MAN.");
			else if (mode == AUTO)
				strcat(topbuffer, " AUTO");

			else if (direction == STOPPED)
				strcpy(botbuffer, "Ready.      ----");
			else if (direction == FILLING)
				strcpy(botbuffer, "Filling.    <---");
			else if (direction == DISPENSING)
				strcpy(botbuffer, "Dispensing. --->");
		}

		display.write((uint8_t*)topbuffer, 16);
		display.setCursor(1, 0); // Might not need if the auto-advance of the cursor brings us down a line
		display.write((uint8_t*)botbuffer, 16);
	}
}
