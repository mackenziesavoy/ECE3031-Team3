#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void tc1_init() {
	// Set A1 and B1 to non-inverting fast 8-bit PWM with no prescale
	// PWM frequency is therefore F_CPU/32768 = 31.25kHz
	TCCR1A = (1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0) | (1 << WGM10);
	TCCR1B = (1 << WGM12) | (1 << CS10);
	DDRB |= (1 << 1) | (1 << 2); // OC1A (PB1) and OC1B (PB2) are outputs
}

void adc_init() {
	// Put ADC in freerunning mode with 128 prescale
}

void uart0_init() {
#define BAUD 9600
#include <util/setbaud.h> // This calculates proper UBRR values
	UBRR0L = UBRRL_VALUE;
	UBRR0H = UBRRH_VALUE;
}

void setup()
{
	tc1_init();
	adc_init();
	DDRB |= (1 << 5);
}

void loop() {
	PORTB ^= (1 << 5); // Toggle PB5
	OCR1AL = 0x00; // Set channel A to minimum value
	OCR1BL = 0xFF; // Set channel B to maximum value
	if (ADCSRA & (1 << ADIF)) {
		// If ADC complete flag is set
		// step the control algorithm with the new data
	}
}
