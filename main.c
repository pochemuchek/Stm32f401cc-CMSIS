#include <stm32f401xc.h>
#include "ADC.h"
#include "PWM.h"
#include "SPI.h"

int main(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER |= GPIO_MODER_MODER13_0;
	GPIOC->MODER &= ~GPIO_MODER_MODER13_1;
	
	/* adc1_init_main(); */
	/* pwm_init_main(); */
	
	spi1_init_main(MASTER);
	
	int i = 1;
	while(1) 
	{
		i++;
		i &= ~1;
	}
	
}