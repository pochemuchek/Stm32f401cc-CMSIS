#include "global.h"

uint8_t flag_delay = 0;

void clock_8Mhz_init(void) {
	RCC->CR &= ~RCC_CR_PLLON;
	while(RCC->CR & RCC_CR_PLLRDY);
	
	RCC->CR |= RCC_CR_HSION; /* HSI oscilator ON */
	while((RCC->CR & RCC_CR_HSIRDY) != RCC_CR_HSIRDY);
	
	/*
		PLL_VCO = ([HSI_VALUE OR HSE_VALUE] / PLL_M) * PLL_N
		SYSCLK = PLL_VCO / PLL_P
	*/
	
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC; /* select HSI 16 MHz clocked PLL */
	
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;
	RCC->PLLCFGR |= (RCC_PLLCFGR_PLLM_1 | RCC_PLLCFGR_PLLM_3); /* PLL_M = 10 */
	
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
	RCC->PLLCFGR |= (RCC_PLLCFGR_PLLN_1 | RCC_PLLCFGR_PLLN_3); /* PLL_N = 10 */
	
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP; /* PLL_P = 2 */
	
	RCC->CR |= RCC_CR_PLLON; /* PLL oscilator ON */
	while((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY);
	
	RCC->CFGR |= (RCC_CFGR_SW_1 | ~RCC_CFGR_SW_0);
	while((RCC->CFGR & RCC_CFGR_SWS_1) != RCC_CFGR_SWS_1);
	
	RCC->CFGR &= ~RCC_CFGR_HPRE;
	
	SystemCoreClockUpdate();
}

void global_init_tim3(int arr, int psc){
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	
	TIM3->ARR = arr - 1;
	TIM3->PSC = psc - 1;
	
	TIM3->DIER |= TIM_DIER_UIE;
	
	NVIC_SetPriority(TIM3_IRQn, 3);
	NVIC_EnableIRQ(TIM3_IRQn);
}

void TIM3_IRQHandler(void){
	TIM3->SR &= ~TIM_SR_UIF;
	GPIOC->ODR ^= GPIO_ODR_ODR_13;
	flag_delay = 1;
	TIM3->CR1 &= ~TIM_CR1_CEN;
}

void delay_ms(int time){
	flag_delay = 0;
	global_init_tim3(time, SystemCoreClock / 1000);
	TIM3->CR1 |= TIM_CR1_CEN;
	while(!flag_delay);
}