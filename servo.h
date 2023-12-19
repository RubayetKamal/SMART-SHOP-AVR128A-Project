#ifndef servo_H
#define servo_H
#include <avr/interrupt.h>

void initPorts();
void initPWM();

volatile int secondFlag = 0;

void initPWM(){
	
	TCCR1A = 0;
	TCCR1A |= (1<<WGM11);
	TCCR1B = (1<<WGM12) | (1<<WGM13);
	
	TCCR1A |= (1<<COM1A1) | (1<<COM1A0);
	TCCR1B |= (1<<CS10);
	ICR1 = 19999;
	TIMSK |= (1<<OCIE1A);
	
}
void initPorts(){
	DDRB |= (1<<5);
	DDRA = 0xF0;  //for keypad
	PORTA = 0x0F;
}

void enableServo(){
	TCCR1B |= (1<<CS10);
}

void disableServo(){
	TCCR1B &= ~(1<<CS10);
}

void openDoor(){
	OCR1A = ICR1 - 1500;
}

void closeDoor(){
	OCR1A = ICR1 - 500;
}

void keepDoorClosed(){
	secondFlag=300;
}
#endif