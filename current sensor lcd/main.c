#include<avr/io.h>
#define F_CPU 8000000UL
#include<util/delay.h>
#include<stdio.h>
double vin;
double vout;
unsigned int value;
char output[6];

void lcd_cmd(char cmd)              //Command sub routine LCD
{
	PORTC=cmd;
	PORTD&=~(1<<0);
	PORTD|=(1<<1);
	_delay_ms(5);
	PORTD&=~(1<<1);
	_delay_ms(5);
}

void lcd_data(char *txt)         //Data sub routine LCD
{
	while(*txt!='\0')
	{
		PORTC=*txt;
		PORTD|=(1<<0);
		PORTD|=(1<<1);
		_delay_ms(5);
		PORTD&=~(1<<1);
		_delay_ms(5);
		txt++;
	}
}

void voltage(void)             //Sub routine to read voltage
{
	ADMUX|=(1<<0);
	ADCSRA|=(1<<6);
	while(ADIF==0);
	value=ADCL|ADCH<<8;
	vout=value*0.00488;             //To determine output Voltage from sensor
	vin=6*vout;                    //To determine real voltage
	sprintf(output,"%.2f",vin);
	lcd_cmd(0xc6);
	lcd_data(output);
}

void current(void)
{
	ADMUX&=~(1<<0);
	ADCSRA|=(1<<6);
	while(ADIF==0);
	value=ADCL|ADCH<<8;
	vout=value*0.00488;            //To determine output voltage from sensor
	vin=(vout-2.5)/0.185;          //To determine real current
	sprintf(output,"%.2f",vin);    //Float to char conversion for printing
	lcd_cmd(0xc6);
	lcd_data(output);
}

int main(void)
{
	DDRC=0xff;
	DDRD=0x03;
	PORTC=0x00;
	PORTD=0x00;
	lcd_cmd(0x38);
	lcd_cmd(0x01);
	lcd_cmd(0x0c);
	lcd_cmd(0x80);
	lcd_data("Current:");
	lcd_cmd(0xc0);
	//lcd_data("Current Bill:");
	ADMUX=0x00;
	ADCSRA=0x87;                     //Initializing A/D converter
	while(1)
	{
		voltage();                  //Voltage display
		      
	}
	return 0;
}