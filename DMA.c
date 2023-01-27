#include "DMA.h"

/*
	DMA is initialize here for using with SPI and I2S
*/
uint8_t dma_arr_tx[SIZE_TX_BUFFER];
uint8_t dma_arr_rx[SIZE_RX_BUFFER];

/*
status_transfer_dma2
	- 0, means transfer not complete
	- 1, means transfer complete
*/
uint8_t status_transfer_dma2 = 0;

uint8_t dma2_return_status(void){
	return status_transfer_dma2;
}

void dma2_init_main(void){
	dma2s3_init_tx();
	dma2s2_init_rx();
}

void dma2s3_init_tx(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN; /* Start clocking dma2*/
	
	DMA2_Stream3->CR &= ~DMA_SxCR_EN; /* disable dma2 */
	while(DMA2_Stream3->CR & DMA_SxCR_EN); /* wait when DAM2 will be ready to configuration */
	
	DMA2_Stream3->PAR |= (uint32_t)(&SPI1->DR); /* set memory addres of peripheral */
	DMA2_Stream3->M0AR |= (uint32_t)(&dma_arr_tx[0]); /* set memory addres of buffer tx, double mode isn't active */
	
	DMA2_Stream3->CR = 0;
	/*
		DMA_SxCR_MSIZE = 0, for byte
		DMA_SxCR_PSIZE = 0, for byte
	  DMA_SxCR_MBURST = 0, for single transfer
		DMA_SxCR_HTIE = 0, HT interrupt disabled 
	*/
	DMA2_Stream3->CR |= (DMA_SxCR_CHSEL_0 | DMA_SxCR_CHSEL_1); /* Chanel selected, 3, spi1_tx*/
	DMA2_Stream3->CR |= DMA_SxCR_PL_0; /* medium priority level */
	DMA2_Stream3->CR |= DMA_SxCR_MINC; /* memory increment enable */
	DMA2_Stream3->CR |= DMA_SxCR_DIR_0;/* direction, from memory to peripheral */
	DMA2_Stream3->CR |= DMA_SxCR_TCIE; /* transfer complete interrupt enable*/
	
	NVIC_SetPriority(DMA2_Stream3_IRQn, 7); /* Set priority for interrupt */
	NVIC_EnableIRQ(DMA2_Stream3_IRQn); /* Enable interrupts */
	
	DMA2_Stream3->CR |= DMA_SxCR_EN; /* enable dma2*/
}

void dma2s2_init_rx(void){
	
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN; /* Start clocking dma2*/
	
	DMA2_Stream2->CR &= ~DMA_SxCR_EN; /* disable dma2 */
	while(DMA2_Stream2->CR & DMA_SxCR_EN); /* wait when DAM2 will be ready to configuration */
	
	DMA2_Stream2->PAR |= (uint32_t)(&SPI1->DR); /* set memory addres of peripheral */
	DMA2_Stream2->M0AR |= (uint32_t)(&dma_arr_rx[0]); /* set memory addres of buffer tx, double mode isn't active */
	
	DMA2_Stream2->CR = 0;
	/*
		DMA_SxCR_MSIZE = 0, for byte
		DMA_SxCR_PSIZE = 0, for byte
	  DMA_SxCR_MBURST = 0, for single transfer
		DMA_SxCR_HTIE = 0, HT interrupt disabled 
	*/
	DMA2_Stream2->CR |= (DMA_SxCR_CHSEL_1); /* Chanel selected, 2, spi1_rx*/
	DMA2_Stream2->CR |= DMA_SxCR_PL_0; /* medium priority level */
	DMA2_Stream2->CR |= DMA_SxCR_MINC; /* memory increment enable */
	DMA2_Stream2->CR |= DMA_SxCR_TCIE; /* transfer complete interrupt enable*/
	
	NVIC_SetPriority(DMA2_Stream2_IRQn, 8); /* Set priority for interrupt */
	NVIC_EnableIRQ(DMA2_Stream2_IRQn); /* Enable interrupts */
	
	DMA2_Stream2->CR |= DMA_SxCR_EN; /* enable dma2*/
}

void DMA2_Stream3_IRQHandler(void){
	if(DMA2->LISR &  DMA_LISR_TCIF3){ /* if true, it means trasfer complete*/
		DMA2->LIFCR |= DMA_LIFCR_CTCIF3; /* clear DMA_LISR_TCIF3 bit */
		status_transfer_dma2= 1; 
	}
}

void DMA2_Stream2_IRQHandler(void){
		if(DMA2->LISR &  DMA_LISR_TCIF2){ /* if true, it means receive complete*/
		DMA2->LIFCR |= DMA_LIFCR_CTCIF2; /* clear DMA_LISR_TCIF2 bit */
			
		status_transfer_dma2 = 1;
	}
}

void dma2_sent_get_1byte(uint8_t* data, uint16_t count_byte){
	status_transfer_dma2 = 0;
	
	/* ---------- get stream ---------- */
	DMA2_Stream2->CR &= ~DMA_SxCR_EN; /* disable dma2 */
	DMA2_Stream2->CR |= DMA_SxCR_MINC; 
	DMA2_Stream2->NDTR = (uint32_t)(count_byte);
	DMA2_Stream2->CR |= DMA_SxCR_EN;
	/* ------------------------------- */
	
	
	/* ---------- sent stream ---------- */
	DMA2_Stream3->CR &= ~DMA_SxCR_EN; /* disable dma2 */
	DMA2_Stream3->CR |= DMA_SxCR_MINC; 
	DMA2_Stream3->NDTR = (uint32_t)(count_byte);
	DMA2_Stream3->CR &=	~DMA_SxCR_MSIZE;/* memmory frame format is byte */
	DMA2_Stream3->CR &=	~DMA_SxCR_PSIZE;/* periph frame format is byte */
	DMA2_Stream3->CR |= DMA_SxCR_EN;
	/* ------------------------------- */
}
	
void dam2_sent_get_2byte(uint8_t* data, uint16_t count_byte){
	status_transfer_dma2 = 0;
	DMA2_Stream2->CR &= ~DMA_SxCR_EN; /* disable dma2 */
	
	
}

void dam2_sent_get_2Nbyte(uint8_t* data, uint16_t count_byte){
	status_transfer_dma2 = 0;
	DMA2_Stream2->CR &= ~DMA_SxCR_EN; /* disable dma2 */
	
	
}
	