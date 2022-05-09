
/*
 *ldr_adc.c
 *
 * Created: 11/10/2020 6:38:08 PM
 * Author : Vickey
 */ 
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>


void InitADC()
{
	ADMUX=(1<<REFS0);									// For Aref=AVcc;
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);	// Prescalar div factor =128
}

uint16_t ReadADC(uint8_t ch)
{
	//Select ADC Channel ch must be 0-7
	ch=ch&0b00000111;
	ADMUX&=0b11100000;
	ADMUX|=ch;

	//Start Single conversion
	ADCSRA|=(1<<ADSC);

	//Wait for conversion to complete
	while(!(ADCSRA & (1<<ADIF)));

	//Clear ADIF by writing one to it
	//Note you may be wondering why we have write one to clear it
	//This is standard way of clearing bits in io as said in datasheets.
	//The code writes '1' but it result in setting bit to '0' !!!

	ADCSRA|=(1<<ADIF);

	return(ADC);
}

void main()
{
	uint16_t adc_result;
   	DDRD=0b00010000; // set pin 4 on port D as output to control the buzzer

   	DDRA&=~(1<<0);
	uint16_t limit=931;
	
	//Initialize ADC
	InitADC();
	
	//Put some intro text into LCD
	
	

	while(1)
	{
		adc_result=ReadADC(0);           // Read Analog value from channel-0
		
		
		if(adc_result<limit){
			PORTD|=(1<<4); //turn on the buzzer
			
		}
		if(adc_result>limit)
		{
			PORTD&=~(1<<4); //turn off the buzzer
		}
	}
}