// Blinks the Builtin In LED on Arduino UNO (ATMega328p) 
// using ~70% duty cycle

// Adjustments
// [1a, 1b] - Adjust the duty cycle
// [2] - Adjust output frequency by adjusting prescaler


#include <avr/io.h>
#include <avr/interrupt.h>

#define toggle_BIT(PORT,BIT) PORT ^= (1<<BIT) //this will flip the bit
#define SET_BIT(PORT,BIT) PORT |= (1<<BIT)
#define CLR_BIT(PORT,BIT) PORT &= ~(1<<BIT)

const unsigned max_count = 65535;
volatile int is_output_high = 0;
const unsigned timer1_compare_match_on = 45000;  // [1a]
const unsigned timer1_compare_match_off = 20535; // [1b]

ISR(TIMER1_COMPB_vect)
{
	is_output_high = is_output_high == 0 ? 1 : 0;
	if (is_output_high)
	{
		SET_BIT(PORTB, PD5);
		ICR1 = timer1_compare_match_on; 
	}
	else
	{
		CLR_BIT(PORTB, PD5);
		ICR1 = timer1_compare_match_off;
	}
}

void setup_isr()
{
	// Set Timer 1 to Mode 12, CTC
	SET_BIT(TCCR1B, WGM12);
	SET_BIT(TCCR1B, WGM13);
	
	// Set Prescaler to 256 to have 0.57 Hz at full count 
	//16 bit timer. Max count is 65535
	//16,000,000 / 2 * 256 * (1+65535) = 0.57 Hz (1/2s on, 1/2s off)
	SET_BIT(TCCR1B, CS12);  // [2] Adjust prescaler to increase frequency
	
	// Enable Timer1 interrupt to use compare mode
	SET_BIT(TIMSK1, OCIE1B);

	// Initially, led is off
	is_output_high = 0;
	CLR_BIT(PORTB, PD5);
	ICR1 = timer1_compare_match_off;
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