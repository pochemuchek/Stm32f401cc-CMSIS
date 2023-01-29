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
	while(1){
		delay_ms(1000);
	}		
}