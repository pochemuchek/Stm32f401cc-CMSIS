#include <stm32f401xc.h>

void adc1_init_gpio(void);
void adc1_init_main(void);
void adc1_init_tim2(void);
void TIM2_IRQHandler(void);
void ADC_IRQHandler(void);
