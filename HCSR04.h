#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include "utility.h"

#define F_CPU 1000000UL
#include "util/delay.h"
#include <avr/interrupt.h>
#include "utility.h"
#include <stdio.h>

#define ECHO_PIN PORTD0
#define TRIG_PIN PORTC2

volatile uint32_t gCounter = 0x00;

void configureTimer3();
void triggerPulse();
volatile int calculateDistance();

void stopTimer3();
void initHCSR04();
void configInterrupt2();

void configureTimer3(){
		
        stopTimer3();
        initHCSR04();
		configInterrupt2();

}
void triggerPulse(){
			// Trigger Pulse
			SET_BIT(PORTC, TRIG_PIN);
			_delay_ms(15);
			CLEAR_BIT(PORTC,TRIG_PIN);
}

volatile int calculateDistance(){
	volatile int u32Range = 0;
	if(gCounter > 0)
	{
		u32Range = (int)(0.017*gCounter);
		_delay_ms(80); //very important delay
	}
	return u32Range;
}

void stopTimer3(){
			// use the clock frequency of the uC 1MHz, but for now the timer must be stopped.
			CLEAR_BIT(TCCR3B, CS30);
			CLEAR_BIT(TCCR3B, CS31);
			CLEAR_BIT(TCCR3B, CS31);
}
void initHCSR04(){
			// configure PD0 as input, enable Pull-up resistor, and PE0 as output.
			CLEAR_BIT(DDRD, ECHO_PIN);
			SET_BIT(PORTD,ECHO_PIN);
			SET_BIT(DDRC,TRIG_PIN);
}

void configInterrupt2(){
			// Configure the external interrupt on the input Echo Pin PDO (INT0)-> Enable INT0
			SET_BIT(EIMSK, INT2);
			// Set sense to the Rising edge:
			SET_BIT(EICRA, ISC20);
			SET_BIT(EICRA, ISC21);
}

void startUltrasonicTimer(){
	SET_BIT(TCCR3B,CS30);

}


void setInterruptforFallingEdge(){
			CLEAR_BIT(EICRA, ISC20);
			SET_BIT(EICRA, ISC21);
}

void stopUltrasonicTimer(){
	CLEAR_BIT(TCCR3B, CS30);
}

void setInterruptForRisingEdge(){
			SET_BIT(EICRA, ISC20);
			SET_BIT(EICRA, ISC21);
}
#endif