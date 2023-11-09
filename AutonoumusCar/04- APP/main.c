#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "DIO_private.h"

#include "TIMER0_config.h"
#include "TIMER0_interface.h"
#include "TIMER0_private.h"

#include "TIMER1_config.h"
#include "TIMER1_interface.h"
#include "TIMER1_private.h"

#include "LCD_config.h"
#include "LCD_interface.h"
#include "LCD_private.h"

#include "AutoCar_interface.h"
#include "AutoCar_private.h"

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>







static volatile int TimerOverflow = 0;

ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;	/* Increment Timer Overflow count */
}




int main(void)
{
	TIMER0_vidInit();
	LCD_vidInit();
	SERVO_vidInit();
	DCMOTOR_vidInit();
	TIMER0_vidSyncSecondsDelay(3);
	LCD_vidPrintWord("STARTING");
	TIMER0_vidSyncSecondsDelay(2);
	char string[10];
	long count;
	double distance = 1.1;
	
	DIO_udtSetPinDirection(DIO_PORTC,DIO_PIN1,DIO_OUTPUT);		
	DIO_udtSetPinValue(DIO_PORTD,DIO_PIN6,DIO_HIGH);

	
	sei();			
	TIMSK = (1 << TOIE1);	
	TCCR1A = 0;
	DIO_udtSetPinDirection(DIO_PORTC,DIO_PIN7,DIO_OUTPUT);		
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN7,DIO_HIGH);
	
	DIO_udtSetPinDirection(DIO_PORTB,DIO_PIN3,DIO_OUTPUT);

	
	SERVO_vidLookForward();
	TIMER0_vidSyncSecondsDelay(1);
	
	while(1)
	{
		
				LCD_udtSendCommand(0x01);
				TIMER0_vidSyncMilliSecondsDelay(20);
				LCD_vidPrintWord("LOOKING FORWARD");
				readultra(&distance);
				TIMER0_vidSyncMilliSecondsDelay(100);
				LCD_vidGoTo(2,0);
				floatToString(distance,string,sizeof(string),2);
				LCD_vidPrintWord(string);
				LCD_vidPrintWord(" CM");
				
				
		if( (int)distance < 20)
				{
					changepath();
				}
				else
				{
					LCD_udtSendCommand(0x01);
					TIMER0_vidSyncMilliSecondsDelay(20);
					DCMOTOR_vidMoveForward();
					LCD_vidPrintWord("MOVING FORWARD");
					LCD_vidGoTo(2,0);
					floatToString(distance,string,sizeof(string),2);
					LCD_vidPrintWord(string);
					LCD_vidPrintWord(" CM");
					TIMER0_vidSyncSecondsDelay(1);
				}
				
	
	

	}
	
	
	
}

void changepath(void)
{
	char string[20];
	double Rdis , Ldis ; 
	DCMOTOR_vidStopMotor();
	TIMER0_vidSyncSecondsDelay(1);
	LCD_udtSendCommand(0x01);
	TIMER0_vidSyncMilliSecondsDelay(20);
	LCD_vidPrintWord("Looking Right");
	SERVO_vidLookRight();
	TIMER0_vidSyncSecondsDelay(1);
	readultra(&Rdis);
	
	LCD_vidGoTo(2,0);
	floatToString(Rdis,string,sizeof(string),2);
	LCD_vidPrintWord(string);
	LCD_vidPrintWord(" CM");
	
	
	TIMER0_vidSyncSecondsDelay(1);
	LCD_udtSendCommand(0x01);
	TIMER0_vidSyncMilliSecondsDelay(20);
	LCD_vidPrintWord("Looking Left");
	SERVO_vidLookLeft();
	TIMER0_vidSyncSecondsDelay(1);
	readultra(&Ldis);
	
	LCD_vidGoTo(2,0);
	floatToString(Ldis,string,sizeof(string),2);
	LCD_vidPrintWord(string);
	LCD_vidPrintWord(" CM");
	TIMER0_vidSyncSecondsDelay(1);
	SERVO_vidLookForward();
	TIMER0_vidSyncMilliSecondsDelay(500);
	
	if((Rdis < 20) && (Ldis < 20) )
	{
		LCD_udtSendCommand(0x01);
		TIMER0_vidSyncMilliSecondsDelay(20);
		LCD_vidPrintWord("ALL WAYS ARE BLOCKED");
		TIMER0_vidSyncSecondsDelay(4);
	}
	else if((int)Rdis > (int)Ldis)
	{
		LCD_udtSendCommand(0x01);
		TIMER0_vidSyncMilliSecondsDelay(20);
		LCD_vidPrintWord("TURNIG RIGHT");
		DCMOTOR_vidTurnRight();
		
	}
	else if ((int)Ldis > (int) Rdis )
	{
		LCD_udtSendCommand(0x01);
		TIMER0_vidSyncMilliSecondsDelay(20);
		LCD_vidPrintWord("TURNIG LEFT");
		DCMOTOR_vidTurnLeft();
		
	}
	else
	{
		DCMOTOR_vidMoveBackward();
		TIMER0_vidSyncMilliSecondsDelay(1000);
		DCMOTOR_vidStopMotor();
	}
	
}
void readultra (double *dis)
{
	char string[10];
	long count;
	double distance;
	
	
	CLR_BIT(TCCR1B,4);
	CLR_BIT(TCCR1B,3);
	CLR_BIT(TCCR1A,1);
	
	
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN1,DIO_HIGH);
	_delay_us(10);
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN1,DIO_LOW);
	
	TCNT1 = 0;	
	TCCR1B = 0x41;	
	TIFR = 1<<ICF1;	
	TIFR = 1<<TOV1;	

	
	
	while ((TIFR & (1 << ICF1)) == 0);
	TCNT1 = 0;	
	TCCR1B = 0x01;	
	TIFR = 1<<ICF1;	
	TIFR = 1<<TOV1;	
	TimerOverflow = 0;

	while ((TIFR & (1 << ICF1)) == 0);
	count = TCNT1 + (65535 * TimerOverflow);	
	
	distance = (double)count / 466.47;
	distance = distance/2;
	
	*dis = distance ;
}
void floatToString(float number, char* buffer, int bufferSize, int decimalPlaces) {
	int intPart = (int)number;
	float decimalPart = number - intPart;

	int intLength = snprintf(buffer, bufferSize, "%d", intPart);
	int bufferIndex = intLength;

	if (decimalPlaces > 0) {
		buffer[bufferIndex] = '.';
		bufferIndex++;
	}

	for (int i = 0; i < decimalPlaces; i++) {
		decimalPart *= 10;
		int digit = (int)decimalPart;
		buffer[bufferIndex] = '0' + digit;
		bufferIndex++;
		decimalPart -= digit;
	}

	buffer[bufferIndex] = '\0';
}


