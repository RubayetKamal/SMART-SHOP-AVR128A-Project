/*
 * keypad.h
 *
 * Created: 08/12/2023 15:56:44
 *  Author: $RHEK00-BS9TAG427UBC
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "utility.h"
#include "OLED_I2C.h"
#include "activeState.h"
////////////////////////////////////////////////////////////////////////////////
//// Company:       Chair for Computer Architecture and System Programming,
//                  University of Kassel
//// Developer:     Samer Telawi
//
//// Description:
//      Keypad Display Project
//
//// Dependencies:
//      avr/io.h
//		utility.h
//
//      File-ID: main.c
//      Created on: 2023
////////////////////////////////////////////////////////////////////////////////

#define F_CPU 1000000UL
#include "util/delay.h"
#include "activeState.h"

#define DELAY_TIME 1000U
// Define an array to hold the 7-Segment display values that match with the keypad.
const uint8_t keys[4][4] = {{0x06, 0x5B, 0x4F, 0x77}, // {1, 2, 3, A},
{0x66, 0x6D, 0x7D, 0x7C}, // {4, 5, 6, B},
{0x07, 0x7F, 0x6F, 0x39}, // {7, 8, 9, C},
{0x1B, 0x3F, 0x76, 0x5E}};// {*, 0, #, D}
void scanKeypad();
void blinkRed();
void pressAtoReset();
uint8_t scanColumns(void);
uint8_t keypad(void);

void scanKeypad()
{
	
	{
		// Set Rows to Logic LOW and Columns to Logic HIGH by enabling Pull-up resistors.
		
		
		// scan Port C (columns) to check if the a key has been pressed.
		// if PINC is not 0x0000 1111 --> a key is pressed and one column is LOW.
		if(PINA !=0x0F)
		{
			u8Key = keypad();
			// Display the pressed key on the 7-Segment display
			
			//_delay_ms(50);
		}
	} // end of while(1)
}

uint8_t scanColumns()
{
	// Columns connections
	// C4 <--> PC0
	// C3 <--> PC1
	// C2 <--> PC2
	// C1 <--> PC3
	uint8_t u8ScanedColumn;
	uint8_t u8Temp = PINA & 0x0F;
	//_delay_ms(3); // delay to avid debouncing.
	switch(u8Temp)
	{
		case 0x0E: // 0b0000 1110 --> C4 is LOW
		u8ScanedColumn = 3;//
		break;
		case 0x0D: // 0b0000 1101 --> C3 is LOW
		u8ScanedColumn = 2;
		break;
		case 0xB: // 0b0000 1011 --> C2 is LOW
		u8ScanedColumn = 1;
		break;
		case 0x07: // 0b0000 0111 --> C1 is LOW
		u8ScanedColumn = 0;
		break;
		default: // no column is detected.
		u8ScanedColumn = 4;
		break;
	}
	return u8ScanedColumn;
}
uint8_t keypad()
{
	// Set all rows to logic HIGH
	PORTA = 0xFF;  //the other F is for pullup resistors in column pins
	uint8_t u8PressedKey;
	uint8_t u8Column;
	uint8_t u8RowPin;
	// the u8RowIndex starts from 0 becuase we use a matrix.
	// Row 1 <--> Pin 7 --> 7 - 0 = 7
	// Row 2 <--> Pin 6 --> 7 - 1 = 6
	// Row 3 <--> Pin 5 --> 7 - 2 = 5
	// Row 4 <--> Pin 4 --> 7 - 3 = 4
	// Set each row to LOGIC LOW and scan columns
	for(uint8_t u8RowIndex = 0; u8RowIndex < 4; u8RowIndex++)
	{
		u8RowPin = 7 - u8RowIndex;
		gpio_clear_pin(PORTA_ID, u8RowPin); //one at a time set to low while the others are high
		// Scan the columns to figure out the combination of the pressed key.
		u8Column = scanColumns();
		if(u8Column < 4)
		{
			u8PressedKey = keys[u8RowIndex][u8Column];
			break;
		}
		else
		{
			// Set this row to high and check the next row.
			gpio_set_pin(PORTA_ID, u8RowPin);
			// if no key is detected, does not show anything on display.
			u8PressedKey = 0x00;
		}
	}
	// set all rows LOW
	return u8PressedKey;
}

void pressAtoReset(){
		while(1){
			blinkRed();
			u8Key = keypad();
			if(u8Key==0x77){
				buzzerOff();
				enableServo();
				break;
			}
			
		}
}

#endif /* KEYPAD_H_ */