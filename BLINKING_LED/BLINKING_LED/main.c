/*
 * BLINKING_LED.c
 *
 * Created: 10/17/2020 9:24:51 AM
 * Author : Vickey
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>//header file for delaying LED bulbs

int main(void)
{
    DDRB =0b00100100;//In binary
	//DDRB =0x24;//In hexadecimal   

    while (1) 
    {
		PORTB = 0b00000100;//turn off 1st led in 6th pin and turn on 2nd led in 3rd pin
		
		
		//PORTB |=(1<<2);         //turn on 2nd led in 3rd  pin using binary operators
		//PORTB &=~(1<<5);        //turn off 1st led in 6th  pin using binary operators
		
		_delay_ms(1000);          //wait 1000 milliseconds
		
		PORTB = 0b00100000;       //turn on 1st led in 6t pin and turn off 2nd LED in 3rd pin
		
		//PORTB |=(1<<5);         //turn on 1st led in 6th  pin using binary operators
		//PORTB &=~(1<<2);        //turn off 2nd led in 3rd  pin using binary operators
		
		
		_delay_ms(1000);	       //wait 1000 milliseconds
		
    }
}

