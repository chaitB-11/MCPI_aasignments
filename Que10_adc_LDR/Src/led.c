/*
 * led.c
 *
 *  Created on: Sep 16, 2025
 *      Author: rahul
 */

#include "led.h"

void LED_INIT(uint8_t pin)
{
	RCC->AHB1ENR |= BV(GPIOD_CLK_EN);
	LED_GPIO->MODER &= ~(BV(pin*2+1));
	LED_GPIO->MODER |= BV(2*pin);
	LED_GPIO->OTYPER &= ~BV(pin);
	LED_GPIO->OSPEEDR &= ~(BV(2*pin)|BV(2*pin+1));
	LED_GPIO->PUPDR &= ~(BV(2*pin)|BV(2*pin+1));
}

void LED_ON(uint8_t pin)
{
	LED_GPIO->ODR |= BV(pin);
}

void LED_OFF(uint8_t pin)
{
	LED_GPIO->ODR &= ~BV(pin);
}
void LED_TOGGLE(uint8_t pin)
{
	LED_GPIO->ODR ^= BV(pin);
}
