/*
 * switch.c
 *
 *  Created on: Sep 13, 2025
 *      Author: sunbeam
 */

#include"switch.h"

void switch_init(uint8_t pin)
{
	//1. Enable clock for Switch GPIO
	RCC->AHB1ENR |= BV(SWITCH_CLK_EN);
	//2. Mode - input
	SWITCH_GPIO->MODER &= ~(BV(pin * 2) | BV(pin * 2 + 1));
	//3. pull up/down - no
	SWITCH_GPIO->PUPDR &= ~(BV(pin * 2) | BV(pin * 2 + 1));
}

uint8_t switch_status(void)
{
	return SWITCH_GPIO->IDR & BV(SWITCH_PIN) ? 1 : 0;
}

