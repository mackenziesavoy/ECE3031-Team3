
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

void setup()
{
  TCCR1A = ((1<<COM1A1)|(1<<COM1B1) | (1<<WGM10));

  
  TCCR1B = ((1<<WGM12)|(1<<CS10));

  OCR1A = 0b0000000000001010;
  OCR1B = 0b0000000000010100;
}
 
 void loop(){
  _delay_ms(1000);
  OCR1A += 0b0000000000001010;
  OCR1B += 0b0000000000001111;
}
