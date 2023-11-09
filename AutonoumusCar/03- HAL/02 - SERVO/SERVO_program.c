#include "STD_TYPES.h"

#include "TIMER1_private.h"
#include "TIMER1_interface.h"
#include "TIMER1_config.h"

void SERVO_vidSetAngle(uint8 u8Angle)
{
/* !Comment Calculate PWM on time using Linear interpolation*/
/*
   SG90 servo motor time for -90° to +90 rotation.
   At ~0.52ms   -90° (0°)      of its rotation.
   At ~1.4ms     0°  (neutral) of its rotation.
   At ~2.4ms    +90° (180°)    of its rotation.
*/
	
	uint16 u16OnTime;
	uint32 Linear ;
	Linear = u8Angle*10.4;
	u16OnTime = 520 + Linear;
	
	
	TIMER1_vidFastPWM_ICR1Top(u16OnTime,20000);
}
