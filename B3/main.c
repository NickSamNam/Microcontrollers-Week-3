/*
 * B3.c
 *
 * Created: 1-3-2018 12:57:44
 * Author : snick
 */ 


#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <stdio.h>

#include "HD44780U.h"

#define COMPARE_15_ms 0x78
#define COMPARE_25_ms 0xC8

void wait(int ms)
{
	int i;
	for (i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}

ISR(TIMER2_COMP_vect)
{
	switch (OCR2)
	{
		case COMPARE_15_ms:
			PORTD &= ~0x80;
			OCR2 = COMPARE_25_ms;
			break;
		case COMPARE_25_ms:
			PORTD |= 0x80;
			OCR2 = COMPARE_15_ms;
			break;
	}
}

int main(void)
{
	DDRD |= 0x80; // Set PD7 as write
	
	// Init timer
	TCCR2 = 0x0D;	// CTC, Prescaler 1024
	OCR2 = COMPARE_15_ms;	// Set compare to 15ms
	TIMSK = 0x80;	// Enable compare interrupt
	sei();	// Enable global interrupts
	
	while(1)
	{
		// keep it alive
	}
}