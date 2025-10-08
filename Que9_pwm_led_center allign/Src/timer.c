/*
 * timer.c
 *
 *  Created on: Apr 4, 2025
 *      Author: admin
 */

#include "timer.h"

void TimerPwmInit(void)
{

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	GPIOC->MODER |= BV(2 * 6 + 1);
	GPIOC->MODER &= ~BV(2 * 6);

	GPIOC->PUPDR &= ~(BV(2 * 6) | BV(2 * 6 + 1));

	GPIOC->AFR[0] |= (3 << (6 * 4));

	RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;

	TIM8->PSC = TIM_PR - 1;
	TIM8->ARR = 100 - 1;
	TIM8->CCR1 = 0;

	TIM8->CCMR1 &= ~(TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC1S_1);
	TIM8->CCER &= ~TIM_CCER_CC1P;
	TIM8->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;

	TIM8->CCMR1 |= TIM_CCMR1_OC1PE;
	TIM8->CR1 |= TIM_CR1_ARPE;

	TIM8->CR1 |= (TIM_CR1_CMS_0 | TIM_CR1_CMS_1);

	TIM8->CCER |= TIM_CCER_CC1E;

	TIM8->BDTR |= TIM_BDTR_MOE;
	TIM8->CR1 |= TIM_CR1_CEN;
}
