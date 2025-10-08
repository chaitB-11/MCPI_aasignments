/*
 * exti.c
 *
 *  Created on: Sep 16, 2025
 *      Author: rahul
 */

#include "extin.h"
#include "led.h"

volatile uint32_t count=0;
void extint_init(void)

{
	//SWITCH
	RCC->AHB1ENR |= BV(SWITCH_CLK_EN);
	SWITCH_GPIO->MODER &= ~(BV(0)|BV(1));

	//EXTERNAL INTRRUPT
	SYSCFG->EXTICR[0] &= ~(BV(0) | BV(1) | BV(2) | BV(3));
		EXTI->IMR |= BV(0);
		EXTI->RTSR |= BV(0);
		NVIC_EnableIRQ(EXTI0_IRQn);
	}

	void EXTI0_IRQHandler(void)
	{

		EXTI->PR |= BV(0);
		LED_ON(14);
		count++;

	}


