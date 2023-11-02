#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER0_interface.h"
#include "TIMER0_config.h"
#include "TIMER0_private.h"


void (*pvFunc_Callback)(void);
uint32 u32NoFlags = 0 ;
	
void TIMER0_vidInit(void)
{
	#if   TIMER0_MODE_OF_OPERATION == TIMER0_NORMAL
		CLR_BIT(TCCR0, 6);
		CLR_BIT(TCCR0, 3);
	#elif TIMER0_MODE_OF_OPERATION == TIMER0_PWM_PHASE_CORRECT
		SET_BIT(TCCR0, 6);
		CLR_BIT(TCCR0, 3);
	#elif TIMER0_MODE_OF_OPERATION == TIMER0_CTC
		CLR_BIT(TCCR0, 6);
		SET_BIT(TCCR0, 3);
	#elif TIMER0_MODE_OF_OPERATION == TIMER0_PWM_FAST
		SET_BIT(TCCR0, 6);
		SET_BIT(TCCR0, 3);
	#else 
		#warning "Invalid mode of operation"
	#endif
	
	#if   TIMER0_PRESCALER_SELECTION == TIMER0_CLK_NO_PRESCALING
		CLR_BIT(TCCR0,2u);
		CLR_BIT(TCCR0,1u);
		SET_BIT(TCCR0,0u);
	#elif TIMER0_PRESCALER_SELECTION == TIMER0_CLK_DIV_8
		CLR_BIT(TCCR0,2u);
		SET_BIT(TCCR0,1u);
		CLR_BIT(TCCR0,0u);
	#elif TIMER0_PRESCALER_SELECTION == TIMER0_CLK_DIV_64
	    CLR_BIT(TCCR0,2u);
		SET_BIT(TCCR0,1u);
		SET_BIT(TCCR0,0u);
	#elif TIMER0_PRESCALER_SELECTION == TIMER0_CLK_DIV_256
	    SET_BIT(TCCR0,2u);
		CLR_BIT(TCCR0,1u);
		CLR_BIT(TCCR0,0u);
	#elif TIMER0_PRESCALER_SELECTION == TIMER0_CLK_DIV_1024
	    SET_BIT(TCCR0,2u);
		CLR_BIT(TCCR0,1u);
		SET_BIT(TCCR0,0u);
	#else 
		#warning "Invalid prescaler selection"
	#endif
	
}

void TIMER0_vidSyncSecondsDelay     (uint16 u16Seconds)
{
	
    uint16 localCounter = 0;
	uint16 u32NumberOfFlags = 0;
	uint16 u16Prescaler;
	float TimerFreq,TickTime,OVF,OVF2;
	u16Prescaler = TIMER0_PRESCALER_SELECTION;
	TimerFreq = (float)16/(float)u16Prescaler;
	TickTime = 1/TimerFreq;
	OVF = TickTime*256;
	u32NumberOfFlags = (u16Seconds*1000000)/OVF;
	OVF2 = (int)(u16Seconds*1000000)%256;
	OVF2 = OVF2*(1/TickTime);
	TCNT0 = OVF2;
	if(OVF2 > 0 )
	{
		u32NumberOfFlags++;
	}
	
	for(localCounter=0 ; localCounter<u32NumberOfFlags ; localCounter++)
	{
		/* !Comment: waiting for overflow*/
		while(GET_BIT(TIFR,0)==0);
		/* !Comment: clearing overflow flag*/
		SET_BIT(TIFR,0);
	}
}

void TIMER0_vidSyncMilliSecondsDelay(uint16 u16MilliSeconds)
{
	
	uint16 localCounter = 0;
	uint16 u32NumberOfFlags = 0;
	uint16 u16Prescaler;
	float TimerFreq,TickTime,OVF,OVF2;
	u16Prescaler = TIMER0_PRESCALER_SELECTION;
	TimerFreq = (float)16000/(float)u16Prescaler;
	TickTime = 1/TimerFreq;
	OVF = TickTime*256;
	u32NumberOfFlags = u16MilliSeconds/OVF;
	
	OVF2 = (int)u16MilliSeconds%256;
	OVF2 = OVF2*(1/TickTime);
	TCNT0 = OVF2;
	if(OVF2 > 0 )
	{
		u32NumberOfFlags++;
	}
	
	for(localCounter=0 ; localCounter<u32NumberOfFlags ; localCounter++)
	{
		/* !Comment: waiting for overflow*/
		while(GET_BIT(TIFR,0)==0);
		/* !Comment: clearing overflow flag*/
		SET_BIT(TIFR,0);
	}
}
void TIMER0_vidSyncMicroSecondsDelay(uint32 u32MicroSeconds)
{
	
	uint16 localCounter = 0;
	uint16 u32NumberOfFlags = 0;
	uint16 u16Prescaler;
	float TimerFreq,TickTime,OVF,OVF2;
	;
	u16Prescaler = TIMER0_PRESCALER_SELECTION;
	TimerFreq = (float)16/(float)u16Prescaler;
	TickTime = 1/TimerFreq;
	OVF = TickTime*256;
	u32NumberOfFlags = (u32MicroSeconds)/OVF;
	OVF2 = (int)(u32MicroSeconds)%256;
	OVF2 = OVF2*(1/TickTime);
	TCNT0 = OVF2;
	if(OVF2 > 0 )
	{
		u32NumberOfFlags++;
	}
	
	for(localCounter=0 ; localCounter<u32NumberOfFlags ; localCounter++)
	{
		/* !Comment: waiting for overflow*/
		while(GET_BIT(TIFR,0)==0);
		/* !Comment: clearing overflow flag*/
		SET_BIT(TIFR,0);
	}
	
}

void TIMER0_vidAsyncSecondsDelay     (uint16 u16Seconds)
{
	uint16 localCounter = 0;
	uint16 u16Prescaler;
	float TimerFreq,TickTime,OVF,OVF2;
	u16Prescaler = TIMER0_PRESCALER_SELECTION;
	TimerFreq = (float)16/(float)u16Prescaler;
	TickTime = 1/TimerFreq;
	OVF = TickTime*256;
	u32NoFlags = (u16Seconds*1000000)/OVF;
	OVF2 = (int)(u16Seconds*1000000)%256;
	OVF2 = OVF2*(1/TickTime);
	TCNT0 = OVF2;
	if(OVF2 > 0 )
	{
		u32NoFlags++;
	}
	SET_BIT(TIMSK,0);
}

void TIMER0_vidAsyncMilliSecondsDelay(uint16 u16MilliSeconds)
{
	
	uint16 localCounter = 0;
	uint16 u16Prescaler;
	float TimerFreq,TickTime,OVF,OVF2;
	u16Prescaler = TIMER0_PRESCALER_SELECTION;
	TimerFreq = (float)16000/(float)u16Prescaler;
	TickTime = 1/TimerFreq;
	OVF = TickTime*256;
	u32NoFlags = u16MilliSeconds/OVF;
	
	OVF2 = (int)u16MilliSeconds%256;
	OVF2 = OVF2*(1/TickTime);
	TCNT0 = OVF2;
	if(OVF2 > 0 )
	{
		u32NoFlags++;
	}
	
		SET_BIT(TIMSK,0);

}

void TIMER0_vidAsyncMicroSecondsDelay(uint32 u32MicroSeconds)
{
	uint16 localCounter = 0;
	uint16 u32NumberOfFlags = 0;
	uint16 u16Prescaler;
	float TimerFreq,TickTime,OVF,OVF2;
	;
	u16Prescaler = TIMER0_PRESCALER_SELECTION;
	TimerFreq = (float)16/(float)u16Prescaler;
	TickTime = 1/TimerFreq;
	OVF = TickTime*256;
	u32NoFlags = (u32MicroSeconds)/OVF;
	OVF2 = (int)(u32MicroSeconds)%256;
	OVF2 = OVF2*(1/TickTime);
	TCNT0 = OVF2;
	if(OVF2 > 0 )
	{
		u32NoFlags++;
	}
	
	
	SET_BIT(TIMSK,0);
}

void TIMER0_vidSetCallBack(void(*PvCallBack)(void))
{
	pvFunc_Callback = PvCallBack;
}

void COUNTER0_vidSyncCount  (uint8 u8Count)
{
	CLR_BIT(TCCR0, 6);
	CLR_BIT(TCCR0, 3);
	
	SET_BIT(TCCR0,2u);
	SET_BIT(TCCR0,1u);
	SET_BIT(TCCR0,0u);
	
	while(TCNT0 != u8Count);
	TCNT0 = 0 ;
}

void COUNTER0_vidAsyncCount (uint8 u8Count)
{
	CLR_BIT(TCCR0, 6);
	CLR_BIT(TCCR0, 3);
	
	SET_BIT(TCCR0,2u);
	SET_BIT(TCCR0,1u);
	SET_BIT(TCCR0,0u);
	
	
	TCNT0 = 256-u8Count;
	SET_BIT(TIMSK,0);
	u32NoFlags=1;
	
	
}

void TIMER0_vidFastPWMInverted(uint8 u8DutyCycle)
{
	float fDutyCycle;
	fDutyCycle = (float)u8DutyCycle/100;
	OCR0 = (255-fDutyCycle*(255+1)) ;
	
	SET_BIT(TCCR0,5);
	SET_BIT(TCCR0,4);
}
void TIMER0_vidFastPWMNonInverted(uint8 u8DutyCycle)
{
	float fDutyCycle;
	fDutyCycle = (float)u8DutyCycle/100;
	OCR0 = (256*fDutyCycle)-1;
	
	SET_BIT(TCCR0,5);
	CLR_BIT(TCCR0,4);
}

void TIMER0_vidPhaseCorrectPWMinverted (uint8 u8DutyCycle)
{
	float fDutyCycle;
	fDutyCycle = (float)u8DutyCycle/100;
	OCR0 = 255 - (fDutyCycle*255);
	SET_BIT(TCCR0,5);
	SET_BIT(TCCR0,4);
}

void TIMER0_vidPhaseCorrectPWMNoninverted (uint8 u8DutyCycle)
{
	float fDutyCycle;
	fDutyCycle = (float)u8DutyCycle/100;
	OCR0 = fDutyCycle*255;
	SET_BIT(TCCR0,5);
	CLR_BIT(TCCR0,4);
}


/*void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{
	static uint32 counter = 0 ;
	counter++;
	if(counter == u32NoFlags) 
	{
	pvFunc_Callback();
	counter = 0 ;
	}
}*/
