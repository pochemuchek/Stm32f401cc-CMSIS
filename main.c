#include <stm32f401xc.h>
#include "ADC.h"

int main(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER |= GPIO_MODER_MODER12_0;
	GPIOA->MODER &= ~GPIO_MODER_MODER12_1;
	
	adc1_init_main();
	int i = 0;
	while(1)
	{
		i++;
	}
	
}