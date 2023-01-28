#include <stm32f401xc.h>
#include "DMA.h"

#define SLAVE 0
#define MASTER 1
#define BYTE 8
#define WORD 16
#define SIZE_SPI_BUFFER 128

void spi1_set_nss(void);
void spi1_clear_nss(void);

void spi1_init_main(int spi_mode);
void spi1_init_master(void);
void spi1_init_slave(void);
void spi1_init_gpio(void);

void spi1_dma2_tx_init(void);
void spi1_dma2_rx_init(void);

void spi1_set_data_format(uint8_t format);
void spi1_dma2_SG_1byte(uint8_t* data, uint16_t count_byte);
void spi1_dma2_SG_2byte(uint16_t* data, uint16_t count_words);
void spi1_dma2_SG_2Nbyte(uint16_t* data, uint16_t count_words);