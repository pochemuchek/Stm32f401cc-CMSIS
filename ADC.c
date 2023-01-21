#include "ADC.h"

uint16_t data = 0;

void adc1_init_tim2(void){
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;/*start clocking of tim2*/
	TIM2->ARR = 6400 ; 
	TIM2->PSC = 200000 ;	/* u need to set time on yours own */
	TIM2->CR2 |= TIM_CR2_MMS_1;/*enable trg0 to output*/
	TIM2->CR1 |= TIM_CR1_CEN; /* enable counter */
}


void adc1_init_gpio(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER |= GPIO_MODER_MODER7; /* analog mode */
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; /* blink led pc13 */
	GPIOC->MODER |= GPIO_MODER_MODER13_0;
	GPIOC->MODER &= ~GPIO_MODER_MODER13_1;
	
}

void ADC_IRQHandler(void){
	data = 0;
	GPIOC->ODR ^= GPIO_ODR_ODR_13;
	if(ADC1->SR & ADC_SR_EOC){
		data = (((ADC1->DR | 0x8000)>>4) & 0xFF);/* it must be tuned for current sensor*/
		if(data > 150){
			GPIOA->ODR |= GPIO_ODR_ODR_12;
		}
		else{
			GPIOA->ODR &= ~GPIO_ODR_ODR_12;
		}
	}
}

void adc1_init_main(void){
	adc1_init_gpio();
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;/* ctart clocking adc1*/

	ADC1->CR2 |= ADC_CR2_ADON;/* POWER UP*/
	ADC1->CR2 |= ADC_CR2_EXTEN_0; /* enable triger of regular group and type is rising edge */
	ADC1->CR2 |= ADC_CR2_EXTSEL_2; /* chanel is trg0 tim2 */
	ADC1->CR2 |= ADC_CR2_EXTSEL_1;
	ADC1->CR2 &= ~ADC_CR2_CONT; /* disable continious mode*/
	ADC1->CR2 |= ADC_CR2_ALIGN; /* left align mode */
	
	ADC1->CR1 |= ADC_CR1_SCAN; /* scan mode */
	ADC1->SQR3 |= (0x07 & ADC_SQR3_SQ1); /*  first conv of 7th chanel adc (pa7)*/
	ADC1->SQR1 &= ~ADC_SQR1_L;/* one conv */

	ADC1->CR1 |= ADC_CR1_EOCIE;
	
	NVIC_SetPriority(ADC_IRQn, 1);
	NVIC_EnableIRQ(ADC_IRQn);
	ADC1->CR2 |= ADC_CR2_SWSTART;/*START CONVERSATION*/
	adc1_init_tim2();
}