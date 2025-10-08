/*
 * SysTick.c
 *
 *  Created on: Sep 30, 2025
 *      Author: sunbeam
 */
#include"SysTick.h"
#include "stm32f4xx.h"

volatile  uint32_t xTicks = 0;

void SysTick_Handler(void) {
	xTicks++;
}



void ST_DelayMs(uint32_t ms) {

	uint32_t curTicks = xTicks;

	uint32_t waitTill = curTicks + ms;
	while(xTicks < waitTill)
		;
}
