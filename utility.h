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
//      File-ID: utility.h
//      Created on: 2023
//////////////////////////////////////////////////////////////////////////////// 
#ifndef UTILITY_H_
#define UTILITY_H_

#include <avr/io.h>

#define ERROR 0xEE
#define MASK(x) ((uint8_t)(1 << x))
// Bit manipulation macros
#define SET_BIT(reg, bit)          ((reg) |= MASK(bit))
#define CLEAR_BIT(reg, bit)        ((reg) &= ~MASK(bit))
#define INVERT_BIT(reg, bit)       ((reg) ^= MASK(bit))
#define READ_BIT(reg, bit)         (((reg) & (1 << (bit))) >> (bit))

// Enum definition for the Ports
typedef enum {
	PORTA_ID, PORTB_ID, PORTC_ID, PORTD_ID, PORTE_ID, PORTF_ID
} PORT_ID;

// Enum definition for the pins mode
typedef enum {
	PIN_MODE_OUTPUT, PIN_MODE_INPUT
} PIN_MODE;
////////////////////////////////////////////////////////////////////////////////
// Function gpio_set_pin writes 1 to a specific bit in a specific port.
// Arguments:
//	port: (A, B, C, D, E, or F) of type PORT_ID
//	pin: the target pin in the specified port
// Return: void 
////////////////////////////////////////////////////////////////////////////////
void gpio_set_pin(PORT_ID port, uint8_t pin);

////////////////////////////////////////////////////////////////////////////////
// Function gpio_clear_pin writes 0 to a specific bit in a specific port.
// Arguments:
//	port: (A, B, C, D, E, or F) of type PORT_ID
//	pin: the target pin in the specified port
// Return: void
////////////////////////////////////////////////////////////////////////////////
void gpio_clear_pin(PORT_ID port, uint8_t pin);

////////////////////////////////////////////////////////////////////////////////
// Function gpio_invert_pin inverts a specific bit in a specific port.
// Arguments:
//	port: (A, B, C, D, E, or F) of type PORT_ID
//	pin: the target pin in the specified port
// Return: void
////////////////////////////////////////////////////////////////////////////////
void gpio_invert_pin(PORT_ID port, uint8_t pin);

////////////////////////////////////////////////////////////////////////////////
// Function gpio_read_pin gets the states of a specific bit in a specific port.
// Arguments:
//	port: (A, B, C, D, E, or F) of type PORT_ID
//	pin: the target pin in the specified port
// Return: 0, 1 or 0xEE (ERROR) of type unit8_t.
////////////////////////////////////////////////////////////////////////////////
uint8_t gpio_read_pin(PORT_ID port, uint8_t pin);

////////////////////////////////////////////////////////////////////////////////
// Function gpio_set_pin_mode sets the mode of a specific pin in a specific port.
// Arguments:
//	port: (A, B, C, D, E, or F) of type PORT_ID
//	pin: the target pin in the specified port
//	mode: pin mode as high or low of type PIN_MODE
// Return: void 
////////////////////////////////////////////////////////////////////////////////
void gpio_set_pin_mode(PORT_ID port, uint8_t pin, PIN_MODE mode);
#endif /* UTILITY_H_ */