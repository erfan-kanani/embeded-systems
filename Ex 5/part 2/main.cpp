# define F_CPU 1000000UL // clock speed is 1MHz
#include<avr/io.h>        // AVR header
#include <util/atomic.h>

char stepper[] = {0x05, 0x06, 0x0A, 0x09};
int state = 0; //0=> not started yet 1=>ClockWise 2=>Anti-ClockWise
int overflow_counter = 0; // count the overflow counts to reach 5ms 
int steper_status = 0; // can have 4 values 0,1,2,3


ISR(TIMER0_OVF_vect){
    overflow_counter++;
    if(overflow_counter == 19){
        if(state == 1){
            PORTA = stepper[steper_status];
            steper_status = (steper_status+1) % 4 ;
        }else if(state == 2){
            PORTA = stepper[steper_status];
            steper_status = (steper_status+3) % 4 ;
        }
        overflow_counter = 0;
    }

}

ISR(INT0_vect){
    if((PINC & 2) == 0){
        if(state == 0 || state == 2){
            state = 1;
        }else{
           state = 2;
        }
    }
}

int main(void)
{
    TIMSK = 0x01; //enable timer0 oveflow interupt
    TCCR0 = 0x01; //timer 0 clock = micro clock with no pre-scaler
    GICR = 1 << INT0; //shift to left to enable interupt 0 
    MCUCR = 1 << ISC00 | 1 << ISC01; //shift to left 
    DDRC = 0x00; //set C to PIN
    DDRA = 0x0F; // set 4 bit of A to PORT
    sei(); //enable all interupts
    while (1)
    {
       
    }
}