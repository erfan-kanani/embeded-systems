#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/atomic.h>

char count = 0;
unsigned char seven_segment(unsigned char number){
    switch (number)
    {
        case 0:
            return 0b0111111;
        case 1:
            return 0b0000110;
            
        case 2:
            return 0b1011011;
            
        case 3:
            return 0b1001111;
            
        case 4:
            return 0b1100110;
            
        case 5:
            return 0b1101101;
            
        case 6:
            return 0b1111101;
            
        case 7:
            return 0b0000111;
            
        case 8:
            return 0b1111111;
            
        case 9:
            return 0b1101111;
            
        default:
            return 0b0000000;
    }
}

ISR(TIMER0_OVF_vect){
    if(PORTC == 0b11111110){
        PORTC = 0b11111101;
        PORTD = seven_segment((count/10) % 10);
    }
    else if(PORTC == 0b11111101 ){
        PORTC = 0b11111011;
        PORTD = seven_segment((count/100) % 10);
    }
    else if(PORTC == 0b11111011 ){
        PORTC = 0b11110111;
        PORTD = seven_segment((count/1000) % 10);
    }
    else {
        PORTC = 0b11111110;
        PORTD = seven_segment(count % 10);
    }
}

ISR(TIMER1_OVF_vect){
        count = (count + 1);
}



int main() 
{
    TIMSK = 0b00000101;
    TCCR1B = 0b0000010;
    TCCR0 = 1 << CS00;
    DDRD = 0xff;
    DDRC = 0xff;
    sei();
    PORTC = ~0x01;
    PORTD = 0;

    while (1)
    {
        
    }
    
    return 0;
}