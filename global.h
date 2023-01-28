#include <stm32f401xc.h>

void clock_8Mhz_init(void);
void clock_12MHz_init(void);

void global_init_tim3(int arr, int psc);
void TIM3_IRQHandler(void);
void delay_ms(int time);