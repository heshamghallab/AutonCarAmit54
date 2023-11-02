
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "DIO_private.h"

#define  Trigger_pin	PC1	/* Trigger pin */

int TimerOverflow = 0;

ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;	/* Increment Timer Overflow count */
}
void ultrinit (void)
{
	DIO_udtSetPinDirection(DIO_PORTC,DIO_PIN1,DIO_OUTPUT);		/* Make trigger pin as output */
	//DIO_udtSetPinDirection(DIO_PORTD,DIO_PIN6,DIO_INPUT);		/* Make trigger pin as output */
	DIO_udtSetPinValue(DIO_PORTD,DIO_PIN6,DIO_HIGH);
	
	sei();			/* Enable global interrupt */
	TIMSK = (1 << TOIE1);	/* Enable Timer1 overflow interrupts */
	TCCR1A = 0;
}
double readsensor (void)
{
	char string[10];
	long count;
	double distance;
	
	/* Give 10us trigger pulse on trig. pin to HC-SR04 */
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN1,DIO_HIGH);
	_delay_us(10);
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN1,DIO_LOW);
	
	TCNT1 = 0x00;	/* Clear Timer counter */
	TCCR1B = 0x41;	/* Capture on rising edge, No prescaler*/
	TIFR = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
	TIFR = 1<<TOV1;	/* Clear Timer Overflow flag */

	/*Calculate width of Echo by Input Capture (ICP) */
	
	while ((TIFR & (1 << ICF1)) == 0);/* Wait for rising edge */
	TCNT1 = 0;	/* Clear Timer counter */
	TCCR1B = 0x01;	/* Capture on falling edge, No prescaler */
	TIFR = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
	TIFR = 1<<TOV1;	/* Clear Timer Overflow flag */
	TimerOverflow = 0;/* Clear Timer overflow count */

	while ((TIFR & (1 << ICF1)) == 0);/* Wait for falling edge */
	count = ICR1 + (65535 * TimerOverflow);	/* Take count */
	/* 8MHz Timer freq, sound speed =343 m/s */
	distance = (double)count / 466.47;
	_delay_ms(200);
	
	return distance;
}