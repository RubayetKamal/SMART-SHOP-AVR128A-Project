/*
 * u8x8_atmega88_hal.c
 *
 * Created: 08.03.2017 09:58:34
 *  Author: mbc
 */ 

#include "u8x8.h"
#include "u8g2.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "u8x8_atmega88_hal.h"
#include "i2c_master.h"
#include <string.h>

//////////////////////////////////////////////////////////////////////////
// STATISCHE VARIABLEN
//////////////////////////////////////////////////////////////////////////

u8x8_t u8x8_ssd1306_s;			// u8x8 Display handle
u8g2_t u8g2_ssd1306_s;					// u8x8 Display handle
char u8x8_strBuffer[20] = {0};			// String buffer


//////////////////////////////////////////////////////////////////////////
// CODE
//////////////////////////////////////////////////////////////////////////


uint8_t u8x8_init_atmega88(void) {
	u8x8_Setup(&u8x8_ssd1306_s, u8x8_d_ssd1306_128x64_vcomh0, u8x8_cad_ssd13xx_i2c, u8x8_byte_atmega88_i2c, u8x8_gpio_and_delay_atmega88);
	
	u8x8_InitDisplay(&u8x8_ssd1306_s);
	u8x8_SetPowerSave(&u8x8_ssd1306_s,0);
	u8x8_ClearDisplay(&u8x8_ssd1306_s);
	u8x8_SetFont(&u8x8_ssd1306_s, u8x8_font_amstrad_cpc_extended_f);
	
	return 0x00;
}

uint8_t u8g2_init_atmega88(void) {
	u8g2_Setup_ssd1306_i2c_128x64_vcomh0_f(&u8g2_ssd1306_s, U8G2_R0, u8x8_byte_atmega88_i2c, u8x8_gpio_and_delay_atmega88);
	//u8g2_Setup_ssd1306_128x64_vcomh0_f

	//u8g2_Setup_ssd1306_128x64_noname_f
	//u8g2_Setup_ssd1306_128x64_noname_f
	u8g2_InitDisplay(&u8g2_ssd1306_s);
	u8g2_SetPowerSave(&u8g2_ssd1306_s,0);
	u8g2_ClearDisplay(&u8g2_ssd1306_s);
	u8g2_SetFont(&u8g2_ssd1306_s, u8g2_font_ncenB14_tr);
	return 0x00;
}

void u8x8_print_value_i8(const char* name, int8_t value, uint8_t x, uint8_t y) {
	char strtmpbuf[5] = {0};
	
	strcpy(u8x8_strBuffer,"                ");		//TODO: length check
	memcpy(u8x8_strBuffer,name, strlen(name));		//TODO: length check
	u8x8_strBuffer[strlen(name)] = ':';
    sprintf(strtmpbuf,"%d", value);
	//itoa((int)value,strtmpbuf,10);
	memcpy(u8x8_strBuffer+strlen(name)+1,strtmpbuf,strlen(strtmpbuf));
	u8x8_DrawString_at(x,y,u8x8_strBuffer);
}

void u8x8_print_value_i16(const char* name, int16_t value, uint8_t x, uint8_t y, uint8_t scale) {
	char strtmpbuf[8] = {0};
	
	strcpy(u8x8_strBuffer,"                ");		//TODO: length check
	memcpy(u8x8_strBuffer,name, strlen(name));		//TODO: length check
	u8x8_strBuffer[strlen(name)] = ':';
    sprintf(strtmpbuf,"%d", value);
	//itoa((int)value,strtmpbuf,10);
	if (scale < strlen(strtmpbuf)) {
		memcpy(u8x8_strBuffer+strlen(name)+1,strtmpbuf,strlen(strtmpbuf)-scale);
		u8x8_strBuffer[strlen(name)+1+strlen(strtmpbuf)-scale] = '.';
		memcpy(u8x8_strBuffer+strlen(name)+2+strlen(strtmpbuf)-scale,strtmpbuf+strlen(strtmpbuf)-scale,scale);
	}
	else {
		memcpy(u8x8_strBuffer+strlen(name)+1,strtmpbuf,strlen(strtmpbuf));
	}
	u8x8_DrawString_at(x,y,u8x8_strBuffer);
}

uint8_t u8x8_byte_atmega88_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	uint8_t *data;
	
	switch(msg)
	{
		case U8X8_MSG_BYTE_SEND:
		data = (uint8_t *)arg_ptr;
		
		while( arg_int > 0 )
		{
			i2c_write(*data);
			data++;
			arg_int--;
		}
		
		break;
		
		case U8X8_MSG_BYTE_INIT:
		//i2c_init(u8x8);
		break;
		case U8X8_MSG_BYTE_SET_DC:
		break;
		case U8X8_MSG_BYTE_START_TRANSFER:
		i2c_start(u8x8_GetI2CAddress(u8x8));	// TODO: muss Adresse geshifftet werden?
		//i2c_start(0x78);
		////i2c_write_byte(u8x8, u8x8_GetI2CAddress(u8x8));
		//i2c_write_byte(u8x8, 0x078);
		break;
		case U8X8_MSG_BYTE_END_TRANSFER:
		i2c_stop();
		break;
		default:
		return 0;
	}
	return 1;
}

uint8_t u8x8_gpio_and_delay_atmega88(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	switch(msg)
	{
		case U8X8_MSG_GPIO_AND_DELAY_INIT:  // called once during init phase of u8g2/u8x8
		break;                            // can be used to setup pins
		case U8X8_MSG_DELAY_NANO:           // delay arg_int * 1 nano second
		break;
		case U8X8_MSG_DELAY_100NANO:        // delay arg_int * 100 nano seconds
		break;
		case U8X8_MSG_DELAY_10MICRO:        // delay arg_int * 10 micro seconds
		break;
		case U8X8_MSG_DELAY_MILLI:          // delay arg_int * 1 milli second
		break;
		case U8X8_MSG_DELAY_I2C:                // arg_int is the I2C speed in 100KHz, e.g. 4 = 400 KHz
		break;                            // arg_int=1: delay by 5us, arg_int = 4: delay by 1.25us
		case U8X8_MSG_GPIO_D0:              // D0 or SPI clock pin: Output level in arg_int
		//case U8X8_MSG_GPIO_SPI_CLOCK:
		break;
		case U8X8_MSG_GPIO_D1:              // D1 or SPI data pin: Output level in arg_int
		//case U8X8_MSG_GPIO_SPI_DATA:
		break;
		case U8X8_MSG_GPIO_D2:              // D2 pin: Output level in arg_int
		break;
		case U8X8_MSG_GPIO_D3:              // D3 pin: Output level in arg_int
		break;
		case U8X8_MSG_GPIO_D4:              // D4 pin: Output level in arg_int
		break;
		case U8X8_MSG_GPIO_D5:              // D5 pin: Output level in arg_int
		break;
		case U8X8_MSG_GPIO_D6:              // D6 pin: Output level in arg_int
		break;
		case U8X8_MSG_GPIO_D7:              // D7 pin: Output level in arg_int
		break;
		case U8X8_MSG_GPIO_E:               // E/WR pin: Output level in arg_int
		break;
		case U8X8_MSG_GPIO_CS:              // CS (chip select) pin: Output level in arg_int
		break;
		case U8X8_MSG_GPIO_DC:              // DC (data/cmd, A0, register select) pin: Output level in arg_int
		break;
		case U8X8_MSG_GPIO_RESET:           // Reset pin: Output level in arg_int
		break;
		case U8X8_MSG_GPIO_CS1:             // CS1 (chip select) pin: Output level in arg_int
		break;
		case U8X8_MSG_GPIO_CS2:             // CS2 (chip select) pin: Output level in arg_int
		break;
		case U8X8_MSG_GPIO_I2C_CLOCK:       // arg_int=0: Output low at I2C clock pin
		break;                            // arg_int=1: Input dir with pullup high for I2C clock pin
		case U8X8_MSG_GPIO_I2C_DATA:            // arg_int=0: Output low at I2C data pin
		break;                            // arg_int=1: Input dir with pullup high for I2C data pin
		case U8X8_MSG_GPIO_MENU_SELECT:
		u8x8_SetGPIOResult(u8x8, /* get menu select pin state */ 0);
		break;
		case U8X8_MSG_GPIO_MENU_NEXT:
		u8x8_SetGPIOResult(u8x8, /* get menu next pin state */ 0);
		break;
		case U8X8_MSG_GPIO_MENU_PREV:
		u8x8_SetGPIOResult(u8x8, /* get menu prev pin state */ 0);
		break;
		case U8X8_MSG_GPIO_MENU_HOME:
		u8x8_SetGPIOResult(u8x8, /* get menu home pin state */ 0);
		break;
		default:
		u8x8_SetGPIOResult(u8x8, 1);          // default return value
		break;
	}
	return 1;
}