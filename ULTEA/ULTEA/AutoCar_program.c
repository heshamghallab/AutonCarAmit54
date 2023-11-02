#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_private.h"

#include "SERVO_interface.h"

#include "TIMER0_interface.h"
#include "TIMER0_private.h"
#include "TIMER0_config.h"

#include "AutoCar_private.h"


#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>




void DCMOTOR_vidInit(void)
{
	DIO_udtSetPinDirection(DIO_PORTD,DIO_PIN4,DIO_OUTPUT);
	DIO_udtSetPinDirection(DIO_PORTD,DIO_PIN3,DIO_OUTPUT);
	DIO_udtSetPinDirection(DIO_PORTC,DIO_PIN3,DIO_OUTPUT);
	DIO_udtSetPinDirection(DIO_PORTC,DIO_PIN4,DIO_OUTPUT);
	DIO_udtSetPinDirection(DIO_PORTC,DIO_PIN5,DIO_OUTPUT);
	DIO_udtSetPinDirection(DIO_PORTC,DIO_PIN6,DIO_OUTPUT);

}
void DCMOTOR_vidMoveForward(void)
{
	
	
	DIO_udtSetPinValue(DIO_PORTD,DIO_PIN3,DIO_HIGH);
	DIO_udtSetPinValue(DIO_PORTD,DIO_PIN4,DIO_HIGH);
	
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN3,DIO_LOW);  // H_IN1
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN5,DIO_LOW);  // H_IN3
	
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN4,DIO_HIGH);  // H_IN2
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN6,DIO_HIGH);  // H_IN4
	
	
	
}


void DCMOTOR_vidMoveBackward(void)
{
	DIO_udtSetPinValue(DIO_PORTD,DIO_PIN3,DIO_HIGH);
	DIO_udtSetPinValue(DIO_PORTD,DIO_PIN4,DIO_HIGH);
	
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN3,DIO_HIGH);  // H_IN1
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN5,DIO_HIGH);  // H_IN3
	
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN4,DIO_LOW);  // H_IN2
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN6,DIO_LOW);  // H_IN4
	
	
}

void DCMOTOR_vidStopMotor (void)
{
	DIO_udtSetPinValue(DIO_PORTD,DIO_PIN3,DIO_LOW);
	DIO_udtSetPinValue(DIO_PORTD,DIO_PIN4,DIO_LOW);

	
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN3,DIO_LOW);  // H_IN1
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN5,DIO_LOW);  // H_IN3
	
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN4,DIO_LOW);  // H_IN2
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN6,DIO_LOW);  // H_IN4
	
}


void SERVO_vidInit(void)
{
	DIO_udtSetPinDirection(DIO_PORTD,DIO_PIN5,DIO_OUTPUT);
	//DIO_udtSetPinDirection(DIO_PORTC,DIO_PIN0,DIO_OUTPUT);
}
void SERVO_vidLookForward(void)
{
	SERVO_vidSetAngle(90);
	
	
}
void SERVO_vidLookRight(void)
{
		SERVO_vidSetAngle(30);
		
		
}
void SERVO_vidLookLeft(void)
{
		SERVO_vidSetAngle(160);
	
}

void DCMOTOR_vidTurnRight(void)
{
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN3,DIO_HIGH);  // H_IN1
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN5,DIO_LOW);  // H_IN3
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN4,DIO_LOW);  // H_IN2
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN6,DIO_HIGH);  // H_IN4
	TIMER0_vidSyncSecondsDelay(1);
	DCMOTOR_vidStopMotor();
	TIMER0_vidSyncSecondsDelay(1);
	DCMOTOR_vidMoveForward();
	
}
void DCMOTOR_vidTurnLeft(void)
{
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN3,DIO_LOW);  // H_IN1
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN5,DIO_HIGH);  // H_IN3
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN4,DIO_HIGH);  // H_IN2
	DIO_udtSetPinValue(DIO_PORTC,DIO_PIN6,DIO_LOW);  // H_IN4
	TIMER0_vidSyncSecondsDelay(1);
	DCMOTOR_vidStopMotor();
	TIMER0_vidSyncSecondsDelay(1);
	DCMOTOR_vidMoveForward();
}


