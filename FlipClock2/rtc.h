/*
 * rtc.h
 *
 * Created: 12/23/2019 3:49:41 PM
 *  Author: drola
 */ 


#ifndef RTC_H_
#define RTC_H_


#include <stdint.h>

struct Time {
	uint8_t h;
	uint8_t m;
	uint8_t s;
	uint8_t u128s; //Counts one 128th of a second
};


struct Time rtc_gettime();
void rtc_settime(uint8_t h, uint8_t m, uint8_t s, uint8_t u128s);
void rtc_init();
void vRtcTask( void *pvParameters );


#endif /* RTC_H_ */