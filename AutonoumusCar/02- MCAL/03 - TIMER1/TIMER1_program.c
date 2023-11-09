#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER1_config.h"
#include "TIMER1_private.h"
#include "TIMER1_interface.h"

void TIMER1_vidFastPWM_ICR1Top
(
uint16 u16OnTime,
uint16 u16Period
)
{
	/* !Comment: Clear OC1A on compare match, set OC1A at TOP */
	SET_BIT(TCCR1A,7);
	CLR_BIT(TCCR1A,6);
	
	/* !Comment: Waveform Generation Mode With ICR1 as TOP */
	SET_BIT(TCCR1B,4);
	SET_BIT(TCCR1B,3);
	SET_BIT(TCCR1A,1);
	CLR_BIT(TCCR1A,0);
	
	/* !Comment: Prescaler select (64)*/
	CLR_BIT(TCCR1B,2);
	SET_BIT(TCCR1B,1);
	SET_BIT(TCCR1B,0);
	/*
	freq = 16MHZ
	presclaer = 64 
	Timer Freq = 16MHZ/64 = 250KHZ
	TickTime = 1/250KHZ = 4 usec
	OVF = MAX period than can be aquired using this presclaer
	OVF = TOP * TickTime = 2^16 * 4 usec = 262.144 msec
	TOP = OVF(period)/Ticktime
	CompMatch = OnTime/Ticktime;  
	*/
		
	ICR1  = 4999;
	OCR1A = u16OnTime/4;
}


