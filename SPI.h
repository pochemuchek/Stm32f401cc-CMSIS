#include <stm32f401xc.h>
#include "DMA.h"

#define SLAVE 0
#define MASTER 1
#define SIZE_SPI_BUFFER 128

void spi1_set_nss(void);
void spi1_clear_nss(void);

void spi1_init_main(int spi_mode);
void spi1_init_master(void);
void spi1_init_slave(void);
void spi1_init_gpio(void);

void spi1_dma_tx_init(void);
void spi1_dma_rx_init(void);
	