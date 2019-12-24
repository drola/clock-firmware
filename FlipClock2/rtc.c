#include "rtc.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include "serial.h"
#include <avr/pgmspace.h>

static struct {
	struct Time time;
	volatile uint8_t timerOverflows;
} rtcState;


ISR(TIMER2_COMPA_vect) {
	rtcState.timerOverflows += 1;
}

void rtc_init() {
	ASSR = ((uint8_t) 1 << AS2); //Run from external 32.768kHz crystal
	TCCR2A =  ((uint8_t) 1 << WGM21);
	TCCR2B = ((uint8_t) 1 << CS22) | ((uint8_t) 1 << CS20); // divide by 1 pre-scaling
	TIMSK2 = ((uint8_t) 1 << OCIE2A); //Enable compare interrupt
	OCR2A = (uint8_t) 1;
}

void rtc_run() {
	uint8_t prev_s = rtcState.time.s;

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		rtcState.time.u128s += rtcState.timerOverflows;
		rtcState.timerOverflows = 0;
	}

	rtc_settime(rtcState.time.h, rtcState.time.m, rtcState.time.s, rtcState.time.u128s);


	//REWORK
	/*
	if(prev_s != rtcState.time.s) {
		static const char str1[] PROGMEM = "Time: ";
		xSerialPrint_P(str1);
		static const char str2[] PROGMEM = "%02d";
		xSerialPrintf_P(str2, rtcState.time.h);
		static const char str3[] PROGMEM = ":";


		xSerialPrint_P(str3);
		xSerialPrintf_P(str2, rtcState.time.m);
		xSerialPrint_P(str3);

		xSerialPrintf_P(str2, rtcState.time.s);
		xSerialPrintLn();

	} */
}

//TODO: This one should be private. Possible race conditions
void rtc_settime(uint8_t h, uint8_t m, uint8_t s, uint8_t u128s) {
	rtcState.time.h = h;
	rtcState.time.m = m;
	rtcState.time.s = s;
	rtcState.time.u128s = u128s;

	
	while(rtcState.time.u128s >= 128) {
		rtcState.time.u128s -= 128;
		rtcState.time.s++;
	}
	while(rtcState.time.s >= 60) {
		rtcState.time.s -= 60;
		rtcState.time.m++;
	}
	while(rtcState.time.m >= 60) {
		rtcState.time.m -= 60;
		rtcState.time.h++;
	}
	while(rtcState.time.h >= 24) {
		rtcState.time.h -= 24;
	}
}

struct Time rtc_gettime() {
	return rtcState.time;
}
