#include <stm32f401xc.h>

#define SIZE_RX_BUFFER 128
#define SIZE_TX_BUFFER 128

void dma_init_main(void);
void dma2_init_tx(void);
void dma2_init_rx(void);
void DMA2_Stream3_IRQHandler(void);
	