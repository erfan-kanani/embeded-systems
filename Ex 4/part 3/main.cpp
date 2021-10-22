#ifndef F_CPU
# define F_CPU 1000000UL // clock speed is 1MHz
#endif
#include<avr/io.h>        // AVR header
#include<util/delay.h>    // delay header
#include <util/atomic.h>
#include <stdio.h>
#include "lcd.h"
//******************LCD PROGRAM STARTS*********************//

#define LCD_DATA PORTB          // port B is selected as LCD data port

#define ctrl PORTD              //  port D is selected as LCD command port

#define en PD7                  // enable signal is connected to port D pin 7

#define rw PD6                  // read/write signal is connected to port D pin 6

#define rs PD5                  // register select signal is connected to port D pin 5


int count , sec  = 0 ;
char St[20];


ISR(TIMER2_COMP_vect){
	count ++;
	bool flag = true;
	if(count == 9){
		count = 0;
		sec--;
		if(sec == 0){
		flag = false;
		PORTC = 0x01;
		LCD_cmd(0x80);
		LCD_Write_String("Alarm , LED ON");

		}
		if(flag)
		{
		LCD_cmd(0x80);
		sprintf(St,"%03d",sec);
		PORTC = 0x01;
		LCD_Write_String(St);
		}
		
	}

}

int main(void)

{
	DDRB=0xFF;              // set LCD data port as output
	DDRD=0xE0;              // set LCD signals (RS, RW, E) as out put
	init_LCD();             // initialize LCD
	_delay_ms(10);         // delay of 100 Milli seconds
	LCD_cmd(0x0C);          // display on, cursor off
	_delay_ms(10);
	TIMSK = 0x80;
	TCCR2 = 0x0F;
	OCR2 = 0x60;
	DDRA = 0x00;
	DDRC = 0xff;
	char X[20];
	
	while (1)
    {
		if((PINA & 0x01) != 0){
			
			sec++;
			sprintf(X , "%02d" , sec);
			LCD_cmd(0x80);
			LCD_Write_String(X);
		}
		if((PINA & 0x02) != 0 && sec != 0){
			sec--;
			sprintf(X , "%02d" , sec);
			LCD_cmd(0x80);
			LCD_Write_String(X);
		}
		if((PINA & 0x80 )!= 0){
			sei();
		}
    }
	return 0;

}



