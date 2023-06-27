#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//needed clocks to overflow after 1 sec
#define ticks 976

unsigned char sec=0;
unsigned char min=0;
unsigned char hours=0;

//reset:
void INT0_init(){
	DDRD &=~(1<<PD2);
	PORTD |=  (1<<2);
	MCUCR = (1<<ISC01);
	GICR = (1<<INT0);
}

ISR(INT0_vect){
	sec=0;
	min=0;
	hours=0;
}

//pause:
void INT1_init(){
	DDRD&=~(1<<PD3);
	MCUCR|=(1<<ISC11)|(1<<ISC10);
	GICR |=(1<<INT1);
}

ISR(INT1_vect){
	TCCR1B=0;
}

//resume:
void INT2_init(){
	DDRB&=~(1<<PB2);
	PORTB|=(1<<PB2);
	MCUCSR|=(1<<ISC2);
	GICR|=(1<<INT2);
}

ISR(INT2_vect){
	TCCR1B =(1<<WGM12)|(1<<CS12)|(1<<CS10);
}

//Timer:
void Timer1_init(){
	TCNT1=0;
	OCR1A=ticks;
	TIMSK=(1<<OCIE1A);
	/*TCCR1A:
	 * Normal Compare mode: clear COM1A and B
	 * Non PWM mode: set FOC1A and B
	 * Work on mode 4: clear WGM11 and  WGM10
	 * */
	TCCR1A = (1<<FOC1A)| (1<<FOC1B );
	/*TCCR1B:
	 * Work on mode 4: clear WGM13 and  set WGM12
	 * work with N=1024: set CS12 and CS10 but clear CS11
	 * */
	TCCR1B =(1<<WGM12)|(1<<CS12)|(1<<CS10);
}

ISR(TIMER1_COMPA_vect)
{
	sec++;
	if(sec == 60){
		sec=0;
		min++;
	}
	if(min == 60){
		min=0;
		hours++;
	}
	if(hours==99){
		hours=0;
	}
}

int main(){
	/*enable/disable pins:output pins*/
	DDRA |=0x3F;

	/*7-segments*/
	DDRC |=0x0F;

	//enable global interrupt bit
	SREG |=(1<<7);

	Timer1_init();
	INT0_init();
	INT1_init();
	INT2_init();

	while(1){
		//display:

		PORTA = 0x01;
		PORTC = (PORTC & 0xf0) | (sec%10);
		_delay_ms(2);

		PORTA = 0x02;
		PORTC = (PORTC & 0xf0) | (sec/10);
		_delay_ms(2);

		PORTA = 0x04;
		PORTC = (PORTC & 0xf0) | (min%10);
		_delay_ms(2);

		PORTA = 0x08;
		PORTC = (PORTC & 0xf0) | (min/10);
		_delay_ms(2);

		PORTA = 0b00010000;
		PORTC = (PORTC & 0xf0) | (hours%10);
		_delay_ms(2);

		PORTA = 0b00100000;
		PORTC = (PORTC & 0xf0) | (hours/10);
		_delay_ms(2);

	}
}


