/*
 * main.c
 *
 * Created: 11/7/2020 1:12:39 PM
 *  Author: Vickey
 */ 
#define F_CPU 8000000UL     //defineF_CPU as 8Mhz
#include <avr/io.h>     
#include "lcd.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

int16_t  pulse;
static volatile int i=0;

int US_PINS={5,6,7};                            //input pins for sensors

int main(void)
{
	
	char show_a[16];
	Initialise();
	DDRD = 0b11111011;		        //Define PD2 as echo pin and PIND5,PIND6,PIND7 as trigger pins

	_delay_ms(50);
	GICR |= 1<<INT0;                        //Enable the external interrupt source in general interrupt control register
	MCUCR |= 1<<ISC00;		        //Any logical change on INT0 generates an interrupt request

	sei();
	
	while(1)
	{
 		for (int k=5;k<8;k++)           //Triggering pins before waiting 1 seconds  
 		{
	 		PORTD |= 1<<k;
	 		_delay_us(15);
	 		PORTD &= ~(1<<k);
			 
	 		display(pulse,k);        //Call the display function to calculate the distance and display the value
			 
	 		_delay_ms(100);          //Wait 1 seconds
 		}
	}
}

ISR(INT0_vect)                                   //count the pulses between rising edges and falling edges through interrupts in INT0 pin
{
	if(i == 0)
	{
		TCCR1B |= 1<<CS10;
		i = 1;
	}
	else
	{
		TCCR1B = 0;
		pulse = TCNT1;
		TCNT1 = 0;
		i = 0;
	}
}


void display(int16_t count,int k){      
	
	int16_t count_a = count/58;
	
	char show_a[16],a[5];
	itoa(k-4,a,10);
	Send_A_String("UltraSonic - 0");
	Send_A_String(a);
	GoToMrLCDLocation(1,2);
	Send_A_String("Distance=");
	itoa(count_a,show_a,10);
	Send_A_String(show_a);
	Send_A_String(" ");
	GoToMrLCDLocation(13,2);
	Send_A_String("cm");
	GoToMrLCDLocation(1,1);
}