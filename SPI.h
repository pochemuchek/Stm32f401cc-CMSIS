#include <stm32f401xc.h>

#define SLAVE 0
#define MASTER 1

void spi_init_main(int spi_mode);
void spi_init_master(void);
void spi_init_slave(void);
void spi_init_gpio(void);
	