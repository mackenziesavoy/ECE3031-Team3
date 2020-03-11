/*
  Motor.cpp - Library for controlling motor with an encoder and 
  Created by Mackenzie Savoy, March 3rd, 2020
  Released into the public domain.
*/

// Need to add motor control through Timer/Counter 1
// Needs no prescale, TOP of 255, both OC channels enabled
// Step needs a current control algorithm running inside of the PID

#include "Motor.h"

Motor::Motor(char adc_prescale, long encoder_init){
	ADMUX |= 0b00100111; // Left-adjust output, mux select ADC7
	ADCSRA |= 0b10100111; // Enable, Auto-Trigger, and 128 prescale
	// ADC is free-running by default
	enc.write(encoder_init); // Set initial position to known value from SRAM
}

void Motor::begin(){
	ADCSRA |= 0b01100000; // Start conversion, enable auto-trigger
}

void Motor::end(){
	ADCSRA &= !(0b00100000); // Disable auto-trigger
}

void Motor::step(){
	static const int kP = 1;
	static const int kI = 0;
	static const int kD = 0;
	int ADC_READ;
	
	if(ADCSRA & 0b00010000){ // ADIF flag is set
		ADCSRA |= !(0b00010000); // Clear ADIF flag
		adcRead = ADCH; // Using just the left 8-bitset
		// ADLAR = 1
		// do the fucking PID thing, biiiitch
	}
}

long Motor::read(){
	return enc.read();
}

void Motor::write(long position){
	this.position = position;
}