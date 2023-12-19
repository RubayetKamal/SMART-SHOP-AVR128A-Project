/*
 * flameSensor.h
 *
 * Created: 14/12/2023 13:17:52
 *  Author: $RHEK00-BS9TAG427UBC
 */ 


#ifndef FLAMESENSOR_H_
#define FLAMESENSOR_H_
#define flameAnalogPin 0
#define flameDigitalPin 6

#include "OLED_I2C.h"
void initADC();
int readADC();
void initFlameInterrupt();
void initFlame();
void initADC();

volatile int analogValue;
volatile float digitalValue;
volatile int flameFlag;


void initFlame(){
	DDRF &= ~(1<<0);
	PORTF = (1<<0);
	
	DDRE &= ~(1<<6);
	PORTE |= (1<<6);
	
	initFlameInterrupt();
	initADC();
	
}

void initADC(){
	ADMUX |= (1<<REFS0 | (1<<REFS1));
	ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADEN) | (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	ADCSRA |= (1<<ADIF);
}

int readADC(){
	ADCSRA |= (1<<ADSC);
	
	while(ADCSRA & (1<<ADSC));
	ADCSRA |= (1<<ADIF);
	return ADC;
}

void initFlameInterrupt(){
		EIMSK |= (1<<INT6);
		EICRB |= (1<<ISC60);
		EICRB |= (1<<ISC61);

}

int flameToDigital(){
	analogValue = readADC();
	digitalValue =analogValue * (5.0/1024.0);
	
	if(digitalValue<=3){
		flameFlag++;
	}
	return flameFlag;
}

#endif /* FLAMESENSOR_H_ */