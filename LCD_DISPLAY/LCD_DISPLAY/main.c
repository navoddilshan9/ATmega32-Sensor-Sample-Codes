/*
 * LCD_DISPLAY.c
 *
 * Created: 10/12/2020 9:38:08 AM
 * Author : Vickey
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "i2cmaster.h"
#include "i2c_lcd.h"


int main(void)
{
   
   lcd_init(LCD_BACKLIGHT_ON);			/* Initialize LCD */
   lcd_clear();			/* Clear LCD */
   lcd_goto_xy(0,0);	/* Enter column and row position */
   int i;
   for (i=0;i<10;i++)
   {
	 
	 char count[10];
	 itoa(i,count,10);
	  lcd_puts(count); /*Enter what do you print*/
	  _delay_ms(100);
  }
	  
}

