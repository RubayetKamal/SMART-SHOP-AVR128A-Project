#ifndef INFRARED_H
#define INFRARED_H

void initTransmitter();


void initTransmitter(){
	DDRD &= ~(1<<3);  //input
	PORTD |= (1<<3); //pull up
}

#endif