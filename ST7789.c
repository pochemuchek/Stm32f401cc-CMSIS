#include "ST7789.h"
/*
	pa7 - MOSI(spi) SDA(lcd), data from spi
	pb0 - RES, 0 - reset, 1 - work
	pb1 - DC(data command), 0 - command, 1 - data
	pb2 - BLK, brightness
*/

void st7789_init_gpio(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	
	GPIOB->MODER |= GPIO_MODER_MODER0_0; /* PB0 output mode */
	GPIOB->MODER |= GPIO_MODER_MODER1_0; /* PB1 output mode */
	GPIOB->MODER |= GPIO_MODER_MODER2_0; /* PB2 output mode */
}

void st7789_set_RES(void){
	GPIOB->BSRR |= GPIO_BSRR_BS_0;
}

void st7789_reset_RES(void){
	GPIOB->BSRR |= GPIO_BSRR_BR_0;
}

void st7789_set_DC(void){
	GPIOB->BSRR |= GPIO_BSRR_BS_1;
}

void st7789_reset_DC(void){
	GPIOB->BSRR |= GPIO_BSRR_BR_1;
}

void st7789_set_brightnes(void){
	/*better use pwm, but it is in the future */
	GPIOB->BSRR |= GPIO_BSRR_BS_2;
}

void st7789_init_main(void){
	st7789_init_gpio();
	
	spi1_init_master();
	spi1_set_data_format(BYTE);
	
	st7789_set_brightnes();
}