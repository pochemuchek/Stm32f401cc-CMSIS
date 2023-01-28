#include "global.h"

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
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_3; /* PLL_M = 8 */
	
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_3; /* PLL_N = 8 */
	
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP; /* PLL_P = 2 */
	
	RCC->CR |= RCC_CR_PLLON; /* PLL oscilator ON */
	while((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY);
	
	RCC->CFGR |= (RCC_CFGR_SW_1 | ~RCC_CFGR_SW_0);
	while((RCC->CFGR & RCC_CFGR_SWS_1) != RCC_CFGR_SWS_1);
	
	SystemCoreClockUpdate();
}

void clock_12MHz_init(void){

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
	
}
void delay_ms(int time){
	
}