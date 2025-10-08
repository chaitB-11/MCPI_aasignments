/*
 * uart.c
 *
 *  Created on: Mar 28, 2025
 *      Author: admin
 */

#include "uart.h"

void UartInit(uint32_t baud) {

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	GPIOA->PUPDR &= ~(BV(2*2+1) | BV(2*2) | BV(2*3+1) | BV(2*3));

	GPIOA->MODER |= BV(2*2+1) | BV(2*3+1);
	GPIOA->MODER &= ~(BV(2*2) | BV(2*3));

	GPIOA->AFR[0] = (7 << (2*4)) | (7 << (3*4));

	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	USART2->CR1 = USART_CR1_TE | USART_CR1_RE;

	if(baud == 9600)
		USART2->BRR = 0x0683;
	else if(baud == 38400)
		USART2->BRR = 0x01A1;
	else if(baud == 115200)
		USART2->BRR = 0x008B;

	USART2->CR1 |= USART_CR1_UE;
}

void UartPutch(int ch) {

	USART2->DR = ch;

	while((USART2->SR & USART_SR_TXE) == 0)
		;
}

int UartGetch(void) {

	while((USART2->SR & USART_SR_RXNE) == 0)
		;

	return USART2->DR;
}

void UartPuts(char *str) {
	for(int i=0; str[i] != '\0'; i++)
		UartPutch(str[i]);
}

void UartGets(char *str) {
	int i=0;
	char ch;
	do {
		ch = UartGetch();
		str[i] = ch;
		i++;
	} while(ch != '\r');
	str[i] = '\n';
	i++;
	str[i] = '\0';
}


