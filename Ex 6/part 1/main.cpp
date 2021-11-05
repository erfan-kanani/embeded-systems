
# define F_CPU 1000000UL // clock speed is 1MHz
#include<avr/io.h>        
#include<util/delay.h>
#include <stdlib.h>
#include<stdio.h>   
#include "lcd.c"

int main(void)

{
	DDRB=0xFF;              // set LCD data port as output
	DDRD=0xE0;              // set LCD signals (RS, RW, E) as out pu
	ADCSRA = 0b10100110;    // enable adc , auto trigger mode , preScaler 64
	SFIOR = 0x00;           // free running mode 
	int temp = 0;
	char St[16];
	lcd_init(LCD_DISP_ON);


	while (1)
    {
		lcd_clrscr();
		ADMUX = (0 << REFS1) | (1 << REFS0) | (0 << ADLAR) | 0;
		ADCSRA |= (1 << ADSC); //start conversion
		while ((ADCSRA & (1 << ADIF)) == 0); 
		ADCSRA |= (1 << ADIF); //ADC conversion completes and the Data Registers are updated
		temp = (int)(ADCW/2.05) ; //read ADC data from ADC data register and convert voltage to temp
		sprintf(St , "temp is = %d C",temp);
		lcd_puts(St);
		_delay_ms(100);
    }

	return 0;
}



