#include "DMA.h"

/*
	DMA is initialize here for using with SPI and I2S
*/
uint8_t dma_arr_tx[SIZE_TX_BUFFER];
uint8_t dma_arr_rx[SIZE_RX_BUFFER];

void dma_init_main(void){
	dma2_init_tx();
	dma2_init_rx();
}
void dma2_init_tx(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN; /* Start clocking dma2*/
	
	DMA2_Stream3->CR &= ~DMA_SxCR_EN; /* disable dma2 */
	while(DMA2_Stream3->CR & DMA_SxCR_EN); /* wait when DAM2 will be ready to configuration */
	
	DMA2_Stream3->PAR |= (uint32_t)(&SPI1->DR); /* set memory addres of peripheral */
	DMA2_Stream3->M0AR |= (uint32_t)(&dma_arr_tx[0]); /* set memory addres of buffer tx, double mode isn't active */
	/* DMA2_Stream3->NDTR |= (uint32_t)() */
	
	DMA2_Stream3->CR = 0;
	/*
		DMA_SxCR_MSIZE = 0, for byte
		DMA_SxCR_PSIZE = 0, for byte
	  DMA_SxCR_MBURST = 0, for single transfer
		DMA_SxCR_HTIE = 0, HT interrupt disabled 
	*/
	DMA2_Stream3->CR |= (DMA_SxCR_CHSEL_0 | DMA_SxCR_CHSEL_0); /* Chanel selected, 3, spi1_tx*/
	DMA2_Stream3->CR |= DMA_SxCR_PL_0; /* medium priority level */
	DMA2_Stream3->CR |= DMA_SxCR_MINC; /* memory increment enable */
	DMA2_Stream3->CR |= DMA_SxCR_DIR_0;/* direction, from memory to peripheral */
	DMA2_Stream3->CR |= DMA_SxCR_TCIE; /* transfer complete interrupt enable*/
	
	NVIC_SetPriority(DMA2_Stream3_IRQn, 7); /* Set priority for interrupt */
	NVIC_EnableIRQ(DMA2_Stream3_IRQn); /* Enable interrupts */
	
	DMA2_Stream3->CR |= DMA_SxCR_EN; /* enable dma2*/
}

void dma2_init_rx(void){
		RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN; /* Start clocking dma2*/
	
	DMA2_Stream3->CR &= ~DMA_SxCR_EN; /* disable dma2 */
	while(DMA2_Stream3->CR & DMA_SxCR_EN); /* wait when DAM2 will be ready to configuration */
	
	DMA2_Stream3->PAR |= (uint32_t)(&SPI1->DR); /* set memory addres of peripheral */
	DMA2_Stream3->M0AR |= (uint32_t)(&dma_arr_rx[0]); /* set memory addres of buffer tx, double mode isn't active */
	/* DMA2_Stream3->NDTR |= (uint32_t)() */
	
	DMA2_Stream3->CR = 0;
	/*
		DMA_SxCR_MSIZE = 0, for byte
		DMA_SxCR_PSIZE = 0, for byte
	  DMA_SxCR_MBURST = 0, for single transfer
		DMA_SxCR_HTIE = 0, HT interrupt disabled 
	*/
	DMA2_Stream3->CR |= (DMA_SxCR_CHSEL_0 | DMA_SxCR_CHSEL_0); /* Chanel selected, 3, spi1_tx*/
	DMA2_Stream3->CR |= DMA_SxCR_PL_0; /* medium priority level */
	DMA2_Stream3->CR |= DMA_SxCR_MINC; /* memory increment enable */
	DMA2_Stream3->CR |= DMA_SxCR_TCIE; /* transfer complete interrupt enable*/
	
	NVIC_SetPriority(DMA2_Stream3_IRQn, 8); /* Set priority for interrupt */
	NVIC_EnableIRQ(DMA2_Stream3_IRQn); /* Enable interrupts */
	
	DMA2_Stream3->CR |= DMA_SxCR_EN; /* enable dma2*/
}
	