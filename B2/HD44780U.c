/*
 * HD44780U.c
 *
 * Created: 26-2-2018 17:18:51
 *  Author: snick
 *	Short:	Library for HD44780U LCD as connected to BIGAVR6.
 */

#define F_CPU 8000000

#include "HD44780U.h"

#include <avr/io.h>
#include <util/delay.h>


#define LCD_E 0x08;
#define LCD_RS 0x04;

typedef unsigned char Byte;

void Exec()
{
	PORTC |= LCD_E; // E high
	_delay_ms(1); // Small delay
	PORTC &= ~LCD_E; // E low
	_delay_ms(1); // Small delay
}

/*	Initialise the display.	*/
void LCD_init()
{
	// All PORTC pins to write
	DDRC = 0xFF;
	Exec();
	
	// All low
	PORTC = 0x00;
	Exec();
	
	// Enable 4 bit interface
	PORTC = 0x20;
	Exec();
	
	// Function set (4 bit interface, 2 lines, 5x8 font)
	PORTC = 0x20;
	Exec();
	PORTC = 0x80;
	Exec();
	
	// Clear display
	PORTC = 0x00;
	Exec();
	PORTC = 0x10;
	Exec();
	
	// Return home
	PORTC = 0x00;
	Exec();
	PORTC = 0x20;
	Exec();
	
	// Display (display on, cursor off, blinking off)
	PORTC = 0x00;
	Exec();
	PORTC = 0xC0;
	Exec();
	
	// Entry mode (right, no shift)
	PORTC = 0x00;
	Exec();
	PORTC = 0x60;
	Exec();
}

/*	Write text to the display at the current cursor position.	*/
void LCD_display_text(char* text)
{
	int i;
	for (i = 0; text[i] != '\0'; i++)
	{
		char curr = text[i];
		Byte nibble0 = curr & 0xF0;
		Byte nibble1 = (curr << 4) & 0xF0;
		nibble0 |= LCD_RS;
		nibble1 |= LCD_RS;
		PORTC = nibble0;
		Exec(); // execute data write
		PORTC = nibble1;
		Exec(); // execute data write
	}
}

/*	Move the cursor to the specified location.	*/
void LCD_set_cursor(int position)
{
	Byte nibble0 = position & 0xF0;
	Byte nibble1 = (position << 4) & 0xF0;
	nibble0 |= 0x80;
	PORTC = nibble0;
	Exec(); // execute data write
	PORTC = nibble1;
	Exec(); // execute data write
}
