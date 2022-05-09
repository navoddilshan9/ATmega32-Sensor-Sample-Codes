/*
 * color_Sen.c
 *
 * Created: 11/17/2020 8:12:36 PM
 * Author : Vickey
 */ 
#define  F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "tcs3200.h"

uint32_t MeasureR();
uint32_t MeasureG();
uint32_t MeasureB();
uint32_t MeasureC();

int main(void)
{
	
	//Initialize TCS Library
	InitTCS3200();

	uint8_t x=0;
	int8_t vx=1;

	while(1)
	{
		
		TCSLEDOn();
		uint32_t v1=MeasureC();

		_delay_ms(100);

		TCSLEDOff();
		uint32_t v2=MeasureC();

		uint32_t d=v1-v2;

		if(d>8000)
		{

			//Show
			uint32_t r,g,b;

			TCSLEDOn();

			r=MeasureR();
			g=MeasureG();
			b=MeasureB();

			TCSLEDOff();

			uint32_t smallest;

			if(r<b)
			{
				if(r<g)
				smallest=r;
				else
				smallest=g;
			}
			else
			{
				if(b<g)
				smallest=b;
				else
				smallest=g;
			}

			uint32_t _r,_g,_b;
			smallest=smallest/10;

			_r=r/smallest;
			_g=g/smallest;
			_b=b/smallest;

			
			
			_delay_ms(2000);
		}

		x+=vx;
		if(x==15 || x==0)
		vx=vx*-1;
	}

}

uint32_t MeasureR()
{
	TCSSelectRed();
	uint32_t r;

	_delay_ms(10);
	r=TCSMeasure();

	_delay_ms(10);
	r+=TCSMeasure();

	_delay_ms(10);
	r+=TCSMeasure();

	return r/3.3;

}

uint32_t MeasureG()
{
	TCSSelectGreen();
	uint32_t r;

	_delay_ms(10);
	r=TCSMeasure();

	_delay_ms(10);
	r+=TCSMeasure();

	_delay_ms(10);
	r+=TCSMeasure();

	return r/3;

}

uint32_t MeasureB()
{
	TCSSelectBlue();
	uint32_t r;

	_delay_ms(10);
	r=TCSMeasure();

	_delay_ms(10);
	r+=TCSMeasure();

	_delay_ms(10);
	r+=TCSMeasure();

	return r/4.2;

}

uint32_t MeasureC()
{
	TCSSelectClear();
	uint32_t r;

	_delay_ms(10);
	r=TCSMeasure();

	_delay_ms(10);
	r+=TCSMeasure();

	_delay_ms(10);
	r+=TCSMeasure();

	return r/3;
}
