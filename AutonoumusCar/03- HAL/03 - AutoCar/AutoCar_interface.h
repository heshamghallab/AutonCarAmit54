#ifndef  _AUTOCAR_INTERFACE_H_
#define  _AUTOCAR_INTERFACE_H_


void DCMOTOR_vidInit(void);
void DCMOTOR_vidMoveForward(void);
void DCMOTOR_vidMoveBackward(void);
void DCMOTOR_vidStopMotor (void);

void SERVO_vidInit(void);
void SERVO_vidLookForward(void);
void SERVO_vidLookRight(void);
void SERVO_vidLookLeft(void);


void DCMOTOR_vidTurnRight(void);
void DCMOTOR_vidTurnLeft(void);



#endif