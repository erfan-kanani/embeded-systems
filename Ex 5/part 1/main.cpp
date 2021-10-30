# define F_CPU 1000000UL // clock speed is 1MHz
#include<avr/io.h>        // AVR header
#include <util/atomic.h>
char stepper[] = {0x05, 0x06, 0x0A, 0x09};
bool start = false;
int overflow_counter = 0; //count the overflow interupt 
int steper_status = 0; //status of stepper can be 0,1,2,3


ISR(TIMER0_OVF_vect){
    overflow_counter++;
    if(overflow_counter == 20){
        if(start){
            PORTA = stepper[steper_status];
            steper_status = (steper_status+1) % 4 ; //always stay between 0 and 3 
        }
        overflow_counter = 0;
    }
}

ISR(INT0_vect){
    if((PINC & 2) == 0){
        if(!start){
            start = true;
        }else{
            start = false;
        }
    }
}

int main(void)
{
    TIMSK = 0x01; //enable timer0 overflow interupt 
    TCCR0 = 0x01; //enable timer0 clock with no prescaler
    GICR = 1 << INT0; // shift 1 to left to switch the bit of INT0 to enable interupt0
    MCUCR = 1 << ISC00 | 1 << ISC01; //set interupt0 rising edge
    DDRC = 0x00; // make C to PIN
    DDRA = 0x0F; //make first 4bit of A to PORT
    sei(); //enable all interupts
    while (1)
    {
       
    }
}