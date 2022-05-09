/*
 * IR_Sensor.c
 *
 * Created: 10/17/2020 1:25:19 PM
 * Author : Vickey
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>


int main(void)
{
    DDRB = 0b00000001;//define PORTB as  output pin
	DDRD = 0b00000000;//define PORTC as input pins
	while(1){
		
		int x = PIND & 0b00000001;    //get the input from the sensor to a variable
		
		if (x==0b00000001)
		{
			PORTB = 0x00;			  //switch on the OFF
			
		}else if(x==0b00000000)
		{
			
			PORTB = 0xFF;			  //switch on the ON
			
		}
	}
}

