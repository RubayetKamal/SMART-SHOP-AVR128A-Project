/*
 * activeState.h
 *
 * Created: 10/12/2023 13:00:39
 *  Author: $RHEK00-BS9TAG427UBC
 */ 


#ifndef ACTIVESTATE_H_
#define ACTIVESTATE_H_
#include "OLED_I2C.h"
#include "flameSensor.h"
volatile uint8_t u8Key;
enum State{Opened,Closed};
enum State activeState=Opened;
volatile uint8_t previousKey = 0;

void findActiveState() {
	if (u8Key != previousKey) { //if  new button is pressed, change to new pressed button state
		if (u8Key == 0x3F) {   //if 0 is pressed,the button will be closed
			activeState = Closed;
			displayClosed();
			} else if (u8Key == 0x06) {  //if 1 is pressed, the button will show 1
			activeState = Opened;        
			displayOpened();
		}
		previousKey = u8Key;   //if no new button is pressed remain in that saved state
	}
}



#endif /* ACTIVESTATE_H_ */