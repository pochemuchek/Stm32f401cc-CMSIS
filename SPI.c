#include "SPI.h"

/*
	pa4 - NSS
	pa5 - SCK
	pa6 - MISO
	pa7 - MOSI
*/


void spi_init_gpio(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	
	GPIOA->MODER |= (GPIO_MODER_MODER5_1 | GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1); /* alternating mode for pa5 pa6 and pa7 */
	GPIOA->MODER |= GPIO_MODER_MODER4_0; /* output mode */
	
	GPIOA->AFR[0] |= (GPIO_AFRL_AFRL5_0 | GPIO_AFRL_AFRL5_2); /* AF5 for pa5 */
	GPIOA->AFR[0] |= (GPIO_AFRL_AFRL6_0 | GPIO_AFRL_AFRL6_2); /* AF5 for pa6 */
	GPIOA->AFR[0] |= (GPIO_AFRL_AFRL7_0 | GPIO_AFRL_AFRL7_2); /* AF5 for pa7 */
	
}

void spi_init_main(int spi_mode){
	spi_init_gpio();
	
	if(spi_mode){
		spi_init_master();
	}
	else {
		spi_init_slave();
	}		
}

void spi_init_master(void){
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; /* Start clocking spi1*/
	SPI1->CR1 &= ~SPI_CR1_SPE; /* disable spi*/
	
	
	/*---------- Settings SPI1 ----------*/
	SPI1->CR1 &= ~SPI_CR1_BR;/* F(PCLK) / 2 */
	SPI1->CR1 &= ~SPI_CR1_CPOL; /* Clock polarity, 0*/
	SPI1->CR1 &= ~SPI_CR1_CPHA; /* Clock phase, from 0 to 1*/
	SPI1->CR1 &= ~SPI_CR1_DFF; /* 	8-bit data frame format */
	SPI1->CR1 |= (SPI_CR1_SSM | SPI_CR1_SSI);
	SPI1->CR1 |= SPI_CR1_MSTR;
	/*---------- Settings SPI1 ----------*/
	
}	

void spi_init_slave(void){
	
}	