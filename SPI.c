#include "SPI.h"

/*
	pa4 - NSS
	pa5 - SCK
	pa6 - MISO
	pa7 - MOSI
*/


void spi1_init_gpio(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	
	GPIOA->MODER |= (GPIO_MODER_MODER5_1 | GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1); /* alternating mode for pa5 pa6 and pa7 */
	GPIOA->MODER |= GPIO_MODER_MODER4_0; /* output mode */
	spi1_set_nss();
	
	GPIOA->AFR[0] |= (GPIO_AFRL_AFRL5_0 | GPIO_AFRL_AFRL5_2); /* AF5 for pa5 */
	GPIOA->AFR[0] |= (GPIO_AFRL_AFRL6_0 | GPIO_AFRL_AFRL6_2); /* AF5 for pa6 */
	GPIOA->AFR[0] |= (GPIO_AFRL_AFRL7_0 | GPIO_AFRL_AFRL7_2); /* AF5 for pa7 */
	
}

void spi1_set_nss(void){
	GPIOA->BSRR |= GPIO_BSRR_BS4;
}
void spi1_clear_nss(void){
	GPIOA->BSRR |= GPIO_BSRR_BR4;
}

void spi1_init_main(int spi_mode){
	spi1_init_gpio();
	
	if(spi_mode){
		spi1_init_master();
	}
	else {
		spi1_init_slave();
	}		
}

void spi1_init_master(void){
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; /* Start clocking spi1*/
	SPI1->CR1 &= ~SPI_CR1_SPE; /* disable spi*/
	
	
	/*---------- start Settings SPI1 ----------*/
	
		/*
		SPI_CR1_BR = 0, F(PCLK) / 2
		SPI_CR1_CPOL = 0, Clock polyrity, 0
		SPI_CR1_CPHA = 0, Clock phase, from 0 to 1
		SPI_CR1_DFF = 0, 8-bit data frame format
	*/
	SPI1->CR1 |= (SPI_CR1_SSM | SPI_CR1_SSI);
	SPI1->CR1 |= SPI_CR1_MSTR; /* Master mode selection*/
	
	/*---------- end Settings SPI1 ----------*/
	
	spi1_dma2_rx_init();
	spi1_dma2_tx_init();
	
	SPI1->CR1 |= SPI_CR1_SPE; /* spi enable */
	
}	


void spi1_init_slave(void){
	
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; /* Start clocking spi1*/
	SPI1->CR1 &= ~SPI_CR1_SPE; /* disable spi*/
	SPI1->CR1 = 0;
	SPI1->CR2 = 0;
	
	/*---------- start Settings SPI1 ----------*/
		/*
		SPI_CR1_BR = 0, F(PCLK) / 2
		SPI_CR1_CPOL = 0, Clock polyrity, 0
		SPI_CR1_CPHA = 0, Clock phase, from 0 to 1
		SPI_CR1_DFF = 0, 8-bit data frame format
		SPI_CR1_MSTR = 0, Slave mode selection
		SPI_CR1_SSI = 0,  Internal slave select disable
	*/
	
	SPI1->CR1 |= SPI_CR1_SSM;
	SPI1->CR1 |= SPI_CR1_LSBFIRST; /* this bit must be the same as transiver, LSB mode */
	
	/*---------- end Settings SPI1 ----------*/
	
	spi1_dma2_rx_init();
	spi1_dma2_tx_init();
	
	SPI1->CR1 |= SPI_CR1_SPE; /* spi enable */
}	

void spi1_dma2_tx_init(void){
	dma2s3_init_tx();
	SPI1->CR2 |= SPI_CR2_TXDMAEN;
}
void spi1_dma2_rx_init(void){
	dma2s2_init_rx();
	SPI1->CR2 |= SPI_CR2_RXDMAEN;
	spi1_set_nss();
}

void spi1_set_data_format(uint8_t format){
	SPI1->CR1 &= ~SPI_CR1_SPE; /* disable spi*/
	if(format == BYTE){
		SPI1->CR1 &= ~SPI_CR1_DFF; /* one byte mode*/
	}
	else{
		SPI1->CR1 |= SPI_CR1_DFF;/* two byte mode */
	}
}

void spi1_dma2_SG_1byte(uint8_t* data, uint16_t count_byte){
	spi1_set_data_format(BYTE);
	dma2_send_get_1byte(data, count_byte);
	spi1_clear_nss();
}

void spi1_dma2_SG_2byte(uint16_t* data, uint16_t count_words){
	spi1_set_data_format(WORD);
	dma2_send_get_2byte(data[0], count_words);
	
}

void spi1_dma2_SG_2Nbyte(uint16_t* data, uint16_t count_words){
	spi1_set_data_format(WORD);
	dma2_send_get_2Nbyte(data, count_words);
	
}