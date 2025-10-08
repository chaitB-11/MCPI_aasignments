/*
 * timer.c
 *
 *  Created on: Sep 29, 2025
 *      Author: Sunbeam
 */

#include "timer.h"

void TimerInit(void) {

	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;

	TIM7->PSC = PR - 1;
}

void TimerDelayMs(uint32_t ms) {

	uint32_t cnt = (FPCLK / 1000) * ms / PR;

	TIM7->ARR = cnt - 1;

	TIM7->CNT = 0;

	TIM7->CR1 |= TIM_CR1_CEN;

	while(!(TIM7->SR & TIM_SR_UIF));

	TIM7->SR &= ~TIM_SR_UIF;

	TIM7->CR1 &= ~TIM_CR1_CEN;
}

