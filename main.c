/*
* SMART ROOM.c
*
* Created: 05/12/2023 18:25:48
* Author : $RHEK00-BS9TAG427UBC
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "infrared.h"
#include "timer2.h"
#include "utility.h"
#include "HCSR04.h"
#include "servo.h"
#include "buzzer.h"
#include "keypad.h"
#include "dht.h"
#include "OLED_I2C.h"
#include "RGBLED.h"
#include "flameSensor.h"

volatile uint8_t gFalg = 0x00;

volatile int distance;

volatile int timerFlag = 0;

volatile int buzzerFlag = 0;
volatile int  servoFlag =0;

ISR(INT3_vect){
	buzzerFlag++;
	if(buzzerFlag>=1){
		disableServo(); 
		ring_alarm(); 
		pressAtoReset();
		}else{   
		buzzerOff(); 
		enableServo(); 
		buzzerFlag = 0;
		
	}
}

ISR(INT2_vect)
{
	gFalg++;
	
	if(gFalg == 1)
	{
		
		startUltrasonicTimer();
		
		gCounter = 0; 
		
        setInterruptforFallingEdge();
	}
	
	else
	{
		
		stopUltrasonicTimer();
		
		gCounter = TCNT3;
		gFalg = 0;
		TCNT3 = 0;
		
      setInterruptForRisingEdge();
	}
}

ISR(TIMER1_COMPA_vect){

	if (distance <6)
	{
		openDoor(); 
		
		}else{
		Timer2Count();
		
	}
	
}

ISR(TIMER2_OVF_vect){
	secondFlag++; 
	if(secondFlag >=300){
		closeDoor(); 
		timerFlag = 0; 
		secondFlag = 0;
		disableTimerOverflowInterrupt();
		}
}

 ISR(INT6_vect){
	if(flameFlag>=1){
		displayWarning();
	    EIMSK |= (1<<INT3);
		openDoor();
			     ring_alarm();
				  pressAtoReset();
	}
 }

int main(void)
{
	initPorts();
	initPWM();
	configureTimer3();
	initTransmitter();
	buzzer_init();
	initOLED();
	displayTemperatureAndHumidity();
	initRGBLED();
 	initFlame();
 	 
 	
	sei();
	
	while (1)
	{   TemperatureToRGB();
		flameToDigital();
		scanKeypad();
		findActiveState();
		
		if (activeState == Opened)
		{   displayOpened();
			buzzerOff();   
			triggerPulse();  
			distance = calculateDistance();
			disableBuzzerInterrupt();  
			
		}
		else if (activeState == Closed)
		{
			keepDoorClosed(); 
			enableBuzzerInterrupt(); 	
		}
		
	}
}


