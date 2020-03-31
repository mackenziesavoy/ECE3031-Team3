#include <SPI.h>
#include <SRAM_23LC.h>
#include <Encoder.h>

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

    struct {
        int16_t VelocityIntegrator_DSTATE;
        int16_t UD_DSTATE;
        int16_t UD_DSTATE_p;
        int16_t Integrator_DSTATE;
        int16_t Integrator_DSTATE_f;
    } rtDW;

    // Model step function
    void pidStep()
    {
		if (adcCount == 0)
			return; // If we don't have new data we can't do anything

        int16_t error;
        int16_t rtb_ProportionalGain;
        int16_t rtb_IntegralGain;
        int16_t rtb_IntegralGain_j;
        int16_t rtb_tSamp;
        int16_t rtb_tSamp_g;
        int16_t Integrator;
        int16_t Integrator_f;

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
		static int16_t posIntegral = 0; // For integral
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
		static int16_t curIntegral = 0; // For integral
		curIntegral += curError * curGain.ki * timeStep; // Calculate integral response
		int16_t curDerivative = ((curError - prevCurError) * curGain.kd) / timeStep; // Calculate derivative reponse
		int16_t desiredCurrent = curProportional + curIntegral + curDerivative; // Sum responses
		prevCurError = curError; // Save this error for next iteration

		if (desiredCurrent > 0) {
			if (desiredCurrent > (0xFFFF >> 6))
				desiredCurrent = (0xFFFF >> 6);
			OCR1AL = ( >> 6);
		}
		else {

		}
		

        rtb_ProportionalGain = 20 * error;
        rtb_IntegralGain = 5 * error;
        Integrator = rtDW.Integrator_DSTATE + rtb_IntegralGain;
        error <<= 4;
        rtb_tSamp = error;
        error -= rtDW.UD_DSTATE;
        error = ((Integrator * 4295L < 0L ? -1 : 0) + rtb_ProportionalGain) +
            (int16_t)(error * 2000000LL);
        if (error > 108) {
            error = 108;
        }
        else if (error < -108) {
			error = -108;
        }
        error -= getADC();
        rtb_ProportionalGain = 20 * error;
        rtb_IntegralGain_j = 5 * error;
        Integrator_f = rtDW.Integrator_DSTATE_f + rtb_IntegralGain_j;
        error <<= 4;
        rtb_tSamp_g = error;
        error = ((Integrator_f * 4295L < 0L ? -1 : 0) + rtb_ProportionalGain)
            + (int16_t)((error - rtDW.UD_DSTATE_p) * 2000000LL);
        if (error > 255) {
            error = 255;
        }
        else {
            if (error < 0) {
                error = 0;
            }
        }
        if (error <= 0) {
            error = 0;
        }
        rtY.motorDutyA = 0.00390625 * error;
        rtY.motorDutyB = 0.0;
        rtDW.VelocityIntegrator_DSTATE += rtU.desiredVelocity;
        rtDW.Integrator_DSTATE = Integrator + rtb_IntegralGain;
        rtDW.UD_DSTATE = rtb_tSamp;
        rtDW.Integrator_DSTATE_f = Integrator_f + rtb_IntegralGain_j;
        rtDW.UD_DSTATE_p = rtb_tSamp_g;
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

			// Blah blah calculate values for OCR1AL and OCR1BL based on those two inputs and targetPosition
		}
	}

	void setSpeed(int32_t target) {
		targetSpeed = target;
	}

    void calibrate() {
        motorEncoder.write(0);
        sram.writeByte(0x0000, 0);
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

void adc_init() {
	ADCSRB = (1 << ADTS2); // Automatic conversion trigger from Timer0 overflow every 1.024ms
#ifdef __AVR_atmega328pb__
	DIDR0 = 0x80; // When using ATmega328PB, disable channel 7 digital buffer for power reduction
#endif
	ADMUX = (1 << ADLAR) | (7 << MUX0); // Right-adjust conversion results and use channel 7
	// Enable ADC, start converting, enable continuous conversion, and set prescale to mode 7 (128)
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADATE) | (7 << ADPS0);
}

void uart0_init() {
#define BAUD 9600
#include <util/setbaud.h> // This calculates proper UBRR values
	UBRR0L = UBRRL_VALUE;
	UBRR0H = UBRRH_VALUE;
}

void disable_unused_periph() {
	// For the sake of power reduction and noise reduction, disable all unused peripherals
	// This notable will prevent timers 2, 3, and 4 from operating, but they aren't used for anything
#ifdef __AVR_HAVE_PRR0
	PRR0 = (1 << PRTIM2) | (1 << PRUSART1);
#endif
#ifdef __AVR_HAVE_PRR1
	PRR1 = (1 << PRTWI1) | (1 << PRPTC) | (1 << PRTIM4) | (1 << PRSPI1) | (1 << PRTIM3);
#endif
#ifdef __ AVR_HAVE_PRR
	PRR = (1 << PRTIM2);
#endif
}

Button fill(4, 25);
Button feed(14, 25);
Button speed_inc(16, 25);
Button speed_dec(17, 25);
Button stop(15, 25);

MotorDriver motor();

void setup()
{
	disable_unused_periph();
	tc1_init();
	adc_init();
	DDRB |= (1 << 5);
}

void loop() {
	PORTB ^= (1 << 5); // Toggle PB5

}
