#include <stm32f401xc.h>
#include "global.h"
#include "SPI.h"

#define LCD_HEIGHT 240
#define LCD_WIDTH 240

/*
	pa7 - MOSI(spi) SDA(lcd), data from spi
	pb0 - RES, 0 - reset, 1 - work
	pb1 - DC(data command), 0 - command, 1 - data
	pb2 - BLK, brightness
*/

void st7789_init_gpio(void);

void st7789_set_DC(void);
void st7789_reset_DC(void);

void st7789_set_RES(void);
void st7789_reset_RES(void);

void st7789_set_brightnes(void);

void st7789_init_main(void);

void st7789_write_command(uint8_t command, uint8_t* data, uint8_t size);

