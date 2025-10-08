/*
 * lcd.h
 *
 *  Created on: Sep 16, 2025
 *      Author: rahul
 */

#ifndef LED_H_
#define LED_H_

#include "stm32f407xx.h"

#define BV(n) (1<<(n))
#define GREEN_LED_PIN 12
#define ORANGE_LED_PIN 13
#define RED_LED_PIN 14
#define BLUE_LED_PIN 15

#define GPIOD_CLK_EN 3
#define LED_GPIO GPIOD

void LED_INIT(uint8_t pin);
void LED_ON(uint8_t pin);
void LED_OFF(uint8_t pin);
void LED_TOGGLE(uint8_t pin);


#endif /* LED_H_ */
