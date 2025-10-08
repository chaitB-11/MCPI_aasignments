/*
 * timer.c
 *
 *  Created on: Sep 29, 2025
 *      Author: Sunbeam
 */

#include "timer.h"


void TimerInit(uint32_t ms) {

	RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;

	TIM9->PSC = PR - 1;

	uint32_t cnt = (FPCLK / 1000) * ms / PR;

	TIM9->ARR = cnt - 1;

	TIM9->CNT = 0;

	TIM9->DIER |= TIM_DIER_UIE;

	NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);

	TIM9->CR1 |= TIM_CR1_CEN;
}


void TIM1_BRK_TIM9_IRQHandler(void) {

	if(TIM9->SR & TIM_SR_UIF) {

		TIM9->SR &= ~TIM_SR_UIF;
	}
}


