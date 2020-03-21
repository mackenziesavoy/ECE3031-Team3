
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

void setup()
{
  // Set A1 and B1 to non-inverting fast 8-bit PWM with no prescale
  // PWM frequency is therefore F_CPU/32768 = 31.25kHz
  TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM10);
  TCCR1B = (1<<WGM12) | (1<<CS10);
  DDRB |= (1<<1) | (1<<2) | (1<<5); // PB1, PB2, and PB5 are output
}

void loop(){
  if((PORTB & (1<<5)) == 0)
    PORTB |= (1<<5);
  else
    PORTB &= !(1<<5);
  OCR1AL += 1;
  OCR1BL += 2;
}
