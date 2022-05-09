#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void) {
	DDRB |= 1 << DDB1; // Set pin 9 on arduino to output
	DDRB &= 1<< DDB2;  // Set pin 10 on arduino to input PIR 1
	DDRB &= 1<< DDB3;  // Set pin 11 on arduino to input PIR 2
	DDRB &= 1<< DDB4;  // Set pin 12 on arduino to input PIR 3
	
	TCCR1A |= (1 << WGM11) | (1 << COM1A1);
	TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS11);
	
	ICR1 = 39999;
	while (1)
	{
		
		int PIR1 =1<< DDB2 & PINB;
		int PIR2 =1<< DDB3 & PINB;
		int PIR3 =1<< DDB4 & PINB;
		
		
		if(PIR1&1<<2 && DDB2 && PIR2==0x00 && PIR3==0x00){
			rotate(1);//rotate left
			}else if(PIR1==0x00 && PIR2&1<<3 && PIR3==0x00){
			rotate(2);//no movement
			}else if(PIR1==0x00 && PIR2==0x00 && PIR3&1<<4){
			rotate(3);//rotate right
		}
		rotate(2);//Back to center position
	}
	
	return 0;
}
void rotate(int PIR){
	
	switch(PIR){
		case 1:
		OCR1A = 3999 + 800;
		PORTC=0b000001;//turn on the light
		_delay_ms(10000);
		break;
		case 2:
		OCR1A = 3999;
		PORTC=0b000010;//turn on the light
		_delay_ms(10000);
		break;
		case 3:
		OCR1A = 3999 -800;
		PORTC=0b000100;//turn on the light
		_delay_ms(10000);
		break;
		default:
		_delay_ms(10);
		
	}

}