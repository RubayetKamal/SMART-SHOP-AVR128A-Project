////////////////////////////////////////////////////////////////////////////////
//// Company:       Chair for Computer Architecture and System Programming,
//                  University of Kassel
//// Developer:     Samer Telawi
//
//// Description:
//      utility functions for GPIO handling and manipulation.
//
//// Dependencies:
//      avr/io.h
//
//      File-ID: utility.c
//      Created on: 2023
////////////////////////////////////////////////////////////////////////////////
#include "utility.h"
// Set the specified pin of the given port
void gpio_set_pin(PORT_ID port, uint8_t pin) {
	switch(port) {
		case PORTA_ID:
		SET_BIT(PORTA, pin);  // Set the pin of PORTA
		break;
		case PORTB_ID:
		SET_BIT(PORTB, pin);  // Set the pin of PORTB
		break;
		case PORTC_ID:
		SET_BIT(PORTC, pin);  // Set the pin of PORTC
		break;
		case PORTD_ID:
		SET_BIT(PORTD, pin);  // Set the pin of PORTD
		break;
		case PORTE_ID:
		SET_BIT(PORTE, pin);  // Set the pin of PORTD
		break;
		case PORTF_ID:
		SET_BIT(PORTF, pin);  // Set the pin of PORTD
		break;
		default:
		// Do nothing if invalid port is provided
		break;
	}
}

// Clear the specified pin of the given port
void gpio_clear_pin(PORT_ID port, uint8_t pin) {
	switch(port) {
		case PORTA_ID:
		CLEAR_BIT(PORTA, pin);  // Clear the pin of PORTA
		break;
		case PORTB_ID:
		CLEAR_BIT(PORTB, pin);  // Clear the pin of PORTB
		break;
		case PORTC_ID:
		CLEAR_BIT(PORTC, pin);  // Clear the pin of PORTC
		break;
		case PORTD_ID:
		CLEAR_BIT(PORTD, pin);  // Clear the pin of PORTD
		break;
		case PORTE_ID:
		CLEAR_BIT(PORTE, pin);  // Clear the pin of PORTE
		break;
		case PORTF_ID:
		CLEAR_BIT(PORTF, pin);  // Clear the pin of PORTF
		break;
		default:
		// Do nothing if invalid port is provided
		break;
	}
}

// Invert the specified pin of the given port
void gpio_invert_pin(PORT_ID port, uint8_t pin) {
	switch(port) {
		case PORTA_ID:
		INVERT_BIT(PORTA, pin);  // Toggle the pin of PORTA
		break;
		case PORTB_ID:
		INVERT_BIT(PORTB, pin);  // Toggle the pin of PORTB
		break;
		case PORTC_ID:
		INVERT_BIT(PORTC, pin);  // Toggle the pin of PORTC
		break;
		case PORTD_ID:
		INVERT_BIT(PORTD, pin);  // Toggle the pin of PORTD
		break;
		case PORTE_ID:
		INVERT_BIT(PORTE, pin);  // Toggle the pin of PORTE
		break;
		case PORTF_ID:
		INVERT_BIT(PORTF, pin);  // Toggle the pin of PORTF
		break;
		default:
		// Do nothing if invalid port is provided
		break;
	}
}

// Read the state of the specified pin of the given port
uint8_t gpio_read_pin(PORT_ID port, uint8_t pin) {
	switch(port) {
		case PORTA_ID:
		return READ_BIT(PINA, pin);  // Read the pin of PORTA
		case PORTB_ID:
		return READ_BIT(PINB, pin);  // Read the pin of PORTB
		case PORTC_ID:
		return READ_BIT(PINC, pin);  // Read the pin of PORTC
		case PORTD_ID:
		return READ_BIT(PIND, pin);  // Read the pin of PORTD
		case PORTE_ID:
		return READ_BIT(PINE, pin);  // Read the pin of PORTE
		case PORTF_ID:
		return READ_BIT(PINF, pin);  // Read the pin of PORTF
		default:
		return ERROR;  // Return 0xEE for invalid port
	}
}

// Function gpio_set_pin_mode sets the mode of a specific pin in a specific port.
void gpio_set_pin_mode(PORT_ID port, uint8_t pin, PIN_MODE mode)
{
	switch(mode) {
		case PIN_MODE_INPUT:
		switch(port) {
			case PORTA_ID:
			CLEAR_BIT(DDRA, pin);  // Clear the pin of DDRA
			SET_BIT(PORTA, pin);   // enable Pull-up Resistor
			break;
			case PORTB_ID:
			CLEAR_BIT(DDRB, pin);  // Clear the pin of DDRB
			SET_BIT(PORTB, pin);   // enable Pull-up Resistor
			break;
			case PORTC_ID:
			CLEAR_BIT(DDRC, pin);  // Clear the pin of DDRC
			SET_BIT(PORTC, pin);   // enable Pull-up Resistor
			break;
			case PORTD_ID:
			CLEAR_BIT(DDRD, pin);  // Clear the pin of DDRD
			SET_BIT(PORTD, pin);   // enable Pull-up Resistor
			break;
			case PORTE_ID:
			CLEAR_BIT(DDRE, pin);  // Clear the pin of DDRE
			SET_BIT(PORTE, pin);   // enable Pull-up Resistor
			break;
			case PORTF_ID:
			CLEAR_BIT(DDRF, pin);  // Clear the pin of DDRF
			SET_BIT(PORTF, pin);   // enable Pull-up Resistor
			break;
			default:
			// Do nothing if invalid port is provided
			break;
		}
		break;
		
		case PIN_MODE_OUTPUT:
		switch(port) {
			case PORTA_ID:
			SET_BIT(DDRA, pin);  // Set the pin of DDRA
			break;
			case PORTB_ID:
			SET_BIT(DDRB, pin);  // Set the pin of DDRB
			break;
			case PORTC_ID:
			SET_BIT(DDRC, pin);  // Set the pin of DDRC
			break;
			case PORTD_ID:
			SET_BIT(DDRD, pin);  // Set the pin of DDRD
			break;
			case PORTE_ID:
			SET_BIT(DDRE, pin);  // Set the pin of DDRE
			break;
			case PORTF_ID:
			SET_BIT(DDRF, pin);  // Set the pin of DDRF
			break;
			default:
			// Do nothing if invalid port is provided
			break;
		}
		break;
		default:
		// do nothing
		break;
	}
}