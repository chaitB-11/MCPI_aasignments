/*
 * Timer.h
 *
 *  Created on: Sep 29, 2025
 *      Author: rahul
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "stm32f4xx.h"

#define fpclk 16000000UL
#define PR 16

void TimerPwmInit(void);


#endif /* TIMER_H_ */
