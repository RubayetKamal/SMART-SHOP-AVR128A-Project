/*
 * u8x8_atmega88_hal.h
 *
 * Created: 08.03.2017 10:35:44
 *  Author: mbc
 */ 


#ifndef U8X8_ATMEGA88_HAL_H_
#define U8X8_ATMEGA88_HAL_H_

extern u8x8_t u8x8_ssd1306_s;	// u8x8 Display handle
extern u8g2_t u8g2_ssd1306_s;	// u8g2 Display handle

//////////////////////////////////////////////////////////////////////////
// DEFINES
//////////////////////////////////////////////////////////////////////////

#define u8x8_DrawString_at(x,y,str)	u8x8_DrawString(&u8x8_ssd1306_s, x, y, (const char*) str)

uint8_t u8g2_init_atmega88(void);
uint8_t u8x8_init_atmega88(void);

void u8x8_print_value_i8(const char* name, int8_t value, uint8_t x, uint8_t y);
void u8x8_print_value_i16(const char* name, int16_t value, uint8_t x, uint8_t y, uint8_t scale);
uint8_t u8x8_byte_atmega88_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_gpio_and_delay_atmega88(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

#endif /* U8X8_ATMEGA88_HAL_H_ */