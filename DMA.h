#include <stm32f401xc.h>

#define SIZE_RX_BUFFER 128
#define SIZE_TX_BUFFER 128

void dma2_init_main(void);
void dma2s3_init_tx(void);
void dma2s2_init_rx(void);
uint8_t dma2_return_status(void);

void DMA2_Stream3_IRQHandler(void);
void DMA2_Stream2_IRQHandler(void);

void dma2_sent_get_1byte(uint8_t* data, uint16_t count_byte);
void dam2_sent_get_2byte(uint16_t* data, uint16_t count_word);
void dam2_sent_get_2Nbyte(uint16_t* data, uint16_t count_word);
