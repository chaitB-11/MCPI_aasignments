/*
 * rtc.c
 *
 *  Created on: Sep 30, 2025
 *      Author: sunbeam
 */
#include "rtc.h"

uint32_t Bin2BCD(uint32_t binVal){
	uint32_t unit = binVal %10;
	uint32_t tens = binVal /10;
	uint32_t result = (tens << 4) | unit;
	return result;
}

uint32_t BCD2Bin(uint32_t bcdVal){
	uint32_t unit = bcdVal & 0x0F;
	uint32_t tens = (bcdVal & 0xF0)>>4;
	uint32_t result = (tens * 10 ) + unit;
	return result;
}

void RtcInit(RtcDate_t *dt, RtcTime_t *tm){
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR -> CR |= PWR_CR_DBP;
	RCC -> CSR |= RCC_CSR_LSION;
	while(!(RCC->CSR & RCC_CSR_LSIRDY));

	RCC->BDCR |= RCC_BDCR_RTCSEL_1;
	RCC->BDCR &= ~RCC_BDCR_RTCSEL_0;
	RCC->BDCR |= RCC_BDCR_RTCEN;

	RTC->WPR = 0XCA;
	RTC->WPR = 0X53;

	RTC->ISR |= RTC_ISR_INIT;
	while(!(RTC->ISR & RTC_ISR_INITF));
	RTC->PRER = ((RTC_ASYNC_PR - 1) << RTC_PRER_PREDIV_A_Pos) |
						((RTC_SYNC_PR - 1) << RTC_PRER_PREDIV_S_Pos);
	RtcSetDate(dt);
	RtcSetTime(tm);

	RTC->CR |= RTC_CR_BYPSHAD;
	RTC->ISR &= ~RTC_ISR_INIT;
	PWR->CR &= ~PWR_CR_DBP;

}

void RtcSetDate(RtcDate_t *dt){
	uint32_t date = Bin2BCD(dt->date);
	uint32_t month = Bin2BCD(dt->month);
	uint32_t year = Bin2BCD(dt->year);
	uint32_t weekday = Bin2BCD(dt->weekday);

	uint32_t dr =  (date << RTC_DR_DU_Pos) |
	 	 	 (month << RTC_DR_MU_Pos) |
			 (weekday << RTC_DR_WDU_Pos) |
			 (year << RTC_DR_YU_Pos);
	RTC->DR = dr;
}

void RtcSetTime(RtcTime_t *tm){
	uint32_t hr = Bin2BCD(tm->hr);
	uint32_t min = Bin2BCD(tm->min);
	uint32_t sec = Bin2BCD(tm->sec);

	uint32_t tr = (sec << RTC_TR_SU_Pos) |
						(min << RTC_TR_MNU_Pos) |
						(hr << RTC_TR_HU_Pos);
		RTC->TR = tr;
}
void RtcGetDate(RtcDate_t *dt){
	uint32_t dr = RTC->DR;
	uint32_t date = (dr & (RTC_DR_DT_Msk | RTC_DR_DU_Msk)) >> RTC_DR_DU_Pos;
	dt->date = BCD2Bin(date);
	uint32_t month = (dr & (RTC_DR_MT_Msk | RTC_DR_MU_Msk)) >> RTC_DR_MU_Pos;
	dt->month = BCD2Bin(month);
	uint32_t weekday = (dr & (RTC_DR_WDU_Msk)) >> RTC_DR_WDU_Pos;
	dt->weekday = BCD2Bin(weekday);
	uint32_t year = (dr & (RTC_DR_YT_Msk | RTC_DR_YU_Msk)) >> RTC_DR_YU_Pos;
	dt->year = BCD2Bin(year);
}
void RtcGetTime(RtcTime_t *tm) {
	uint32_t tr = RTC->TR;
	uint32_t sec = (tr & (RTC_TR_ST_Msk | RTC_TR_SU_Msk)) >> RTC_TR_SU_Pos;
	tm->sec = BCD2Bin(sec);
	uint32_t min= (tr & (RTC_TR_MNT_Msk | RTC_TR_MNU_Msk)) >> RTC_TR_MNU_Pos;
	tm->min = BCD2Bin(min);
	uint32_t hr = (tr & (RTC_TR_HT_Msk | RTC_TR_HU_Msk)) >> RTC_TR_HU_Pos;
	tm->hr = BCD2Bin(hr);
}
