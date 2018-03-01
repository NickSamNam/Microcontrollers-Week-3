/*
 * B2.c
 *
 * Created: 28-2-2018 13:39:30
 * Author : snick
 */
 
#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <stdio.h>

#include "HD44780U.h"

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
	TCCR2 = 0x00; // Disable clock source
	TCNT2 = OCR2; // Correct overshooting
	int n = TCNT2;
	char n_str[4];
	sprintf(n_str, "%03d", n);
	LCD_set_cursor(10);
	LCD_display_text(n_str);
	OCR2++; // Raise compare value;
	TCCR2 = 0x07; // Enable clock source
}

ISR(TIMER2_OVF_vect)
{
	OCR2 = 0; // Set compare back to 0
	LCD_set_cursor(0);
	LCD_display_text("#NOLIFE");
	wait(100);
	LCD_set_cursor(0);
	LCD_display_text("#Presses: 000");
}

int main(void)
{
    LCD_init();
	LCD_display_text("#Presses: 000");
	
	// Init IO
	DDRD &= ~0x80; // PD7 = 0
	
	// Init counter0
	TCCR2 = 0x07;	// External clock on T2(PD7), rising edge
	OCR2 = 0x01;	// Set initial compare value to 1
	TIMSK = 0xC0; // Enable TIMERCOUNTER2 Compare Match interrupt and overflow interrupt
	sei(); // Enable global interrupts
	while (1)
	{
		// Keep it running
	}
}
