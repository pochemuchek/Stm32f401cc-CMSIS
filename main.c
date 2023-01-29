#include <stm32f401xc.h>
#include "global.h"
#include "ADC.h"
#include "PWM.h"
#include "SPI.h"


void init_pc13_led(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER |= GPIO_MODER_MODER13_0;
	GPIOC->MODER &= ~GPIO_MODER_MODER13_1;
	
}

int main(void)
{
	clock_8Mhz_init();
	
	/* adc1_init_main(); */
	/* pwm_init_main(); */
	
	spi1_init_main(MASTER);

	int i = 0;
	while(1){
		i++;
	}		
}