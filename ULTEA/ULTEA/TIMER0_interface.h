#ifndef _TIMER0_INTERFACE_H_
#define _TIMER0_INTERFACE_H_

/*Driver MACROS*/
#define TIMER0_NORMAL                1u
#define TIMER0_PWM_PHASE_CORRECT     2u
#define TIMER0_CTC                   3u
#define TIMER0_PWM_FAST              4u

#define TIMER0_CLK_NO_PRESCALING     1u
#define TIMER0_CLK_DIV_8             8u
#define TIMER0_CLK_DIV_64            64u
#define TIMER0_CLK_DIV_256           256u
#define TIMER0_CLK_DIV_1024	         1024u

void TIMER0_vidInit(void);

void TIMER0_vidSyncSecondsDelay     (uint16 u16Seconds);
void TIMER0_vidSyncMilliSecondsDelay(uint16 u16MilliSeconds);
void TIMER0_vidSyncMicroSecondsDelay(uint32 u32MicroSeconds);

void TIMER0_vidSetCallBack(void(*PvCallBack)(void));

void TIMER0_vidAsyncSecondsDelay     (uint16 u16Seconds);
void TIMER0_vidAsyncMilliSecondsDelay(uint16 u16MilliSeconds);
void TIMER0_vidAsyncMicroSecondsDelay(uint32 u32MicroSeconds);

void COUNTER0_vidSyncCount  (uint8 u8Count);
void COUNTER0_vidAsyncCount (uint8 u8Count);


void TIMER0_vidFastPWMInverted(uint8 u8DutyCycle);
void TIMER0_vidFastPWMNonInverted(uint8 u8DutyCycle);


void TIMER0_vidPhaseCorrectPWMinverted (uint8 u8DutyCycle);
void TIMER0_vidPhaseCorrectPWMNoninverted (uint8 u8DutyCycle);



#endif