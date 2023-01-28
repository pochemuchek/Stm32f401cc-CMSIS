#include <stm32f401xc.h>
#include "global.h"
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
	
	/* spi1_init_main(MASTER); */
  clock_8Mhz_init(); 
	int i = 0;
	while(1) 
	{
		for(i = 0; i< 15625;i++){}
		GPIOC->ODR ^= GPIO_ODR_ODR_13;
	}
	
}