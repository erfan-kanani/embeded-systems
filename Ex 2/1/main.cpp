#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/delay.h>
int main()
{
    DDRA = 0xff;
    PORTA = 0x01; 
    while (1){
    _delay_ms(500);
    PORTA ^=1;
    }
    return 0;
}
