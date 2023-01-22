#include "PWM.h"

void pwm_init_gpio(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; /* Start clocking gpioa */
	GPIOA->MODER |= GPIO_MODER_MODER2_1;/* Alternating mode PA2*/
	GPIOA->AFR[0] |= (GPIO_AFRL_AFRL2_1 | GPIO_AFRL_AFRL2_0);/* assign output pin with chanel 1 of tim9 */

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; /* blink led pc13 */
	GPIOC->MODER |= GPIO_MODER_MODER13_0;
	GPIOC->MODER &= ~GPIO_MODER_MODER13_1;
	GPIOC->ODR &= ~GPIO_ODR_ODR_13;
}

void pwm_init_main(void){
	pwm_init_gpio();
	pwm_init_tim9();
	
	/*---------- PWM Settings ----------*/
	
	TIM9->CR1 = 0;
	
	TIM9->CCMR1 = 0;
	TIM9->CCMR1 &= ~TIM_CCMR1_CC1S;/* Set first chanel as output*/
	TIM9->CCMR1 |= ( TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2);/* Set pwm mode 1 */
	TIM9->CCMR1 |= TIM_CCMR1_OC1PE; /* enable preload registr*/
	
	TIM9->CCER = 0;
	TIM9->CCER &= ~TIM_CCER_CC1NP; /* because of chanel mode is output, this bit must be 0 */
	TIM9->CCER &= ~TIM_CCER_CC1P; /* active high */
	TIM9->CCER = 0; 
	TIM9->CCER |= TIM_CCER_CC1E; /* output enable */
	/*---------- PWM Settings ----------*/
	
	pwm_set_duty_cycle(100);
	TIM9->CR1 |= TIM_CR1_CEN; /* Enable counter */
}

void pwm_init_tim9(void){
	RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;/* Start clocking tim2*/
	TIM9->ARR = 6400; /* Set frequency pwm */
	TIM9->PSC = 1;
}

void pwm_set_duty_cycle(uint8_t duty) {
  TIM9->CCR1 = ((uint32_t)duty*TIM9->ARR)/100;
}