// Blinks the Builtin In LED on Arduino UNO (ATMega328p) at varying frequency
// down to 1 Hz using timer interrupts

#include <avr/io.h>
#include <avr/interrupt.h>

#define toggle_BIT(PORT,BIT) PORT ^= (1<<BIT) //this will flip the bit
#define SET_BIT(PORT,BIT) PORT |= (1<<BIT)
#define CLR_BIT(PORT,BIT) PORT &= ~(1<<BIT)

volatile unsigned timer1_compare_match = 0;

ISR(TIMER1_COMPB_vect)
{
	toggle_BIT(PORTB,PD5);
	timer1_compare_match += 3000; // Vary the blink frequency
	ICR1 = timer1_compare_match; 
}

void setup_isr()
{
	// Set Timer 1 to Mode 12, CTC
	SET_BIT(TCCR1B, WGM12);
	SET_BIT(TCCR1B, WGM13);
	
	// Set Prescaler to 256 to have 0.57 Hz at full count 
	//16 bit timer. Max count is 65535
	//16,000,000 / 2 * 256 * (1+65535) = 0.57 Hz (1/2s on, 1/2s off)
	SET_BIT(TCCR1B, CS12);
	
	// Enable Timer1 interrupt to use compare mode
	SET_BIT(TIMSK1, OCIE1B);

	ICR1 = timer1_compare_match;
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