/*
 * HD44780U.h
 *
 * Created: 26-2-2018 17:15:32
 *  Author: snick
	Short:	Library for HD44780U LCD as connected to BIGAVR6.
 */ 


#ifndef HD44780U_H_
#define HD44780U_H_

/*	Initialise the display.	*/
void LCD_init(void);

/*	Write text to the display at the current cursor position.	*/
void LCD_display_text(char* text);

/*	Move the cursor to the specified location.	*/
void LCD_set_cursor(int position);

#endif /* HD44780U_H_ */
