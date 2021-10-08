#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/delay.h>
int main()
{
    DDRB = 0xff;
    PORTB = 0x00; 
    while (1){
    _delay_ms(500);
    PORTB = ~PORTB;
    }
    return 0;
}
