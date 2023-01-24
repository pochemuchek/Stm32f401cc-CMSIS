#include <stm32f401xc.h>

#define SIZE_RX_BUFFER 128
#define SIZE_TX_BEFFER 128

void dma_init_main(void);
void dma_init_tx(void);
void dma_init_rx(void);
	