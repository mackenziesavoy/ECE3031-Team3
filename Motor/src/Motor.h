/*
  Motor.h - Library for controlling motor with an encoder and 
  Created by Mackenzie Savoy, March 3rd, 2020
  Released into the public domain.
*/
#ifndef Motor_h
#define Motor_h

#define ENCODER_OPTIMIZE_INTERRUPTS

#include "Arduino.h"
#include "Encoder.h"

class Motor
{
  public:
		// Set prescale and starting position
    Motor(char adc_prescale, long encoder_init);
		void begin(); // Starts the ADC
		void end(); // Stops the ADC
		void step(); // Checks ADC and completes a PID iteration
		long read(); // Returns encoder value
		void write(long position); // Command motor to position
  private:
		Encoder enc(2, 3); // Encoder on pins 2 and 3
		long position = 0; // Target position
};

#endif