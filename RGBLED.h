/*
 * RGBOLED.c
 *
 * Created: 12/12/2023 14:35:26
 * Author : $RHEK00-BS9TAG427UBC
 */
#include <avr/io.h>
#define GreenPin 1
#define RedPin 2
#define BluePin 3

#define F_CPU 1000000UL
#include "util/delay.h"
void initRGBLED();
void RGBLoop();
void ledOFF();

void initRGBLED() {
  DDRF |= (1 << RedPin);  // outputs
  DDRF |= (1 << GreenPin);
  DDRF |= (1 << BluePin);
  
  ledOFF();
}

void RGBLoop() {
  PORTF &= ~(1 << GreenPin);
  PORTF &= ~(1 << BluePin);
  PORTF |= (1 << RedPin);

  _delay_ms(2000);

  PORTF &= ~(1 << RedPin);
  PORTF &= ~(1 << BluePin);
  PORTF |= (1 << GreenPin);

  _delay_ms(2000);
  PORTF &= ~(1 << GreenPin);
  PORTF &= ~(1 << RedPin);
  PORTF |= (1 << BluePin);

  _delay_ms(2000);
};
void TemperatureToRGB(){
	if(temperatureHigh<20){ //show blue if temperature is 19
		PORTF &= ~(1 << GreenPin);
		PORTF &= ~(1 << RedPin);
		PORTF |= (1 << BluePin);
	}
	else if(temperatureHigh>=20){
		PORTF &= ~(1 << RedPin);
		PORTF &= ~(1 << BluePin);
		PORTF |= (1 << GreenPin);
		}
		else{
		PORTF &= ~(1 << GreenPin);
		PORTF &= ~(1 << BluePin);
		PORTF &= ~(1 << RedPin);
	}
}
void ledOFF()
 { PORTF &= ~((1 << RedPin) | (1 << GreenPin) | (1 << BluePin)); 
 }


void blinkRed(){
			PORTF &= ~(1 << GreenPin);
			PORTF &= ~(1 << BluePin);
			PORTF |= (1 << RedPin);
			_delay_ms(500);
					PORTF &= ~(1 << GreenPin);
					PORTF &= ~(1 << BluePin);
					PORTF &= ~(1 << RedPin);
					_delay_ms(500);
}