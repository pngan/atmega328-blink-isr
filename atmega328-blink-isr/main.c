// Blinks the Builtin In LED on Arduino UNO (ATMega328p) at 1 Hz
// using timer interrupts

#include <avr/io.h>
#include <avr/interrupt.h>

#define toggle_BIT(PORT,BIT) PORT ^= (1<<BIT) //this will flip the bit
#define SET_BIT(PORT,BIT) PORT |= (1<<BIT)
#define CLR_BIT(PORT,BIT) PORT &= ~(1<<BIT)

ISR(TIMER1_COMPB_vect)
{
	toggle_BIT(PORTB,PD5);
}

void setup_isr()
{
	//Mode 12, CTC
	SET_BIT(TCCR1B, WGM12);
	SET_BIT(TCCR1B, WGM13);
	
	ICR1 = 0xFF;
	
	
	//TCCR1B |= 1<<WGM13 | 1<<WGM12;	//Mode 12, CTC
	TIMSK1 |= 1<<OCIE1B; // Enable Timer/Counter1 output compare A match interrupt

	//16 bit timer. Max count is 65535
	//16,000,000 / 2 * 256 * (1+65535) = 0.57 Hz (1/2s on, 1/2s off)
    TCCR1B = 1 << CS12; //256 pre-scaler
}

int main(void)
{
	// Built in LED = Pin13 on board = PortB/BIT5 
	SET_BIT(DDRB,PD5);   // Set Data Direction Register to Output
	
    setup_isr();
	
	sei();
	
    while(1)
    {
		// Do nothing
    }
}