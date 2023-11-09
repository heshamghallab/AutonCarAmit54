#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "DIO_private.h"
#include "DIO_interface.h" 

Std_ReturnType DIO_udtSetPinDirection
(
	uint8 u8Port,
	uint8 u8Pin,
	uint8 u8Direction
)
{
	Std_ReturnType udtReturnValue = E_NOT_OK ; 
	
	if(u8Direction == DIO_OUTPUT)
	{
		switch (u8Port)
		{
		case DIO_PORTA: SET_BIT(DDRA,u8Pin); 
			 udtReturnValue = E_OK;
		     break;
			 
		case DIO_PORTB: SET_BIT(DDRB,u8Pin);
		     udtReturnValue = E_OK; 
		     break;
			 
		case DIO_PORTC: SET_BIT(DDRC,u8Pin);
		     udtReturnValue = E_OK;
		     break;
			 
		case DIO_PORTD: SET_BIT(DDRD,u8Pin);
		     udtReturnValue = E_OK; 
		     break;
			 
		default:
			 /*!Comment: Do nothing */
			 break;
		}
		
	}
	else if (u8Direction == DIO_INPUT)
	{
	switch (u8Port)
		{
		case DIO_PORTA: CLR_BIT(DDRA,u8Pin); 
			 udtReturnValue = E_OK;
		     break;
			 
		case DIO_PORTB: CLR_BIT(DDRB,u8Pin);
		     udtReturnValue = E_OK;
		     break;
			 
		case DIO_PORTC: CLR_BIT(DDRC,u8Pin);
		     udtReturnValue = E_OK; 
		     break;
			 
		case DIO_PORTD: CLR_BIT(DDRD,u8Pin);
		     udtReturnValue = E_OK; 
		     break;
			 
		default:
			 /*!Comment: Do nothing */
			 break;
		}
	}
	else
	{
		/*!Comment: Do nothing */
	}
		
	return udtReturnValue; 
}

Std_ReturnType DIO_udtSetPinValue
(
	uint8 u8Port,
	uint8 u8Pin,
	uint8 u8Value
)
{
	
	Std_ReturnType udtReturnValue = E_NOT_OK ; 
	
	if(u8Value == DIO_HIGH)
	{
		switch (u8Port)
		{
		case DIO_PORTA: SET_BIT(PORTA,u8Pin); 
			 udtReturnValue = E_OK; 
		     break;
			 
		case DIO_PORTB: SET_BIT(PORTB,u8Pin);
		     udtReturnValue = E_OK; 
		     break;
			 
		case DIO_PORTC: SET_BIT(PORTC,u8Pin);
		     udtReturnValue = E_OK; 
		     break;
			 
		case DIO_PORTD: SET_BIT(PORTD,u8Pin);
		     udtReturnValue = E_OK; 
		     break;
			 
		default:
			 /*!Comment: Do nothing */
			 break;
		}
		
	}
	else if (u8Value == DIO_LOW)
	{
	switch (u8Port)
		{
		case DIO_PORTA: CLR_BIT(PORTA,u8Pin); 
			 udtReturnValue = E_OK; 
		     break;
			 
		case DIO_PORTB: CLR_BIT(PORTB,u8Pin);
		     udtReturnValue = E_OK; 
		     break;
			 
		case DIO_PORTC: CLR_BIT(PORTC,u8Pin);
		     udtReturnValue = E_OK; 
		     break;
			 
		case DIO_PORTD: CLR_BIT(PORTD,u8Pin);
		     udtReturnValue = E_OK; 
		     break;
			 
		default:
			 /*!Comment: Do nothing */
			 break;
		}
	}
	else
	{
		/*!Comment: Do nothing */
	}
		
	return udtReturnValue; 
}

Std_ReturnType DIO_udtGetPinValue 
(
	uint8  u8Port,
	uint8  u8Pin,
	uint8* pu8Value
)
{
	Std_ReturnType udtReturnValue = E_NOT_OK ;
	switch (u8Port)
	{
		case DIO_PORTA: *pu8Value = GET_BIT(PINA, u8Pin);
			             udtReturnValue = E_OK; 
			             break;
		case DIO_PORTB: *pu8Value = GET_BIT(PINB, u8Pin);
			             udtReturnValue = E_OK; 
			             break;		
		case DIO_PORTC: *pu8Value = GET_BIT(PINC, u8Pin); 
					     udtReturnValue = E_OK; 
			             break;
		case DIO_PORTD: *pu8Value = GET_BIT(PIND, u8Pin);
			             udtReturnValue = E_OK; 
			             break;
		default:
						 /*!Comment: Do nothing */
						 break;
	}
	return udtReturnValue ;
}

Std_ReturnType DIO_udtSetPortDirection
(
	uint8  u8Port,
	uint8 u8Direction
)
{
	Std_ReturnType udtReturnValue = E_NOT_OK ; 
	if(u8Direction == DIO_OUTPUT)
	{
		switch (u8Port)
		{
		case DIO_PORTA: DDRA = 0xFF; 
			 udtReturnValue = E_OK;
		     break;
			 
		case DIO_PORTB: DDRB = 0xFF;
		     udtReturnValue = E_OK; 
		     break;
			 
		case DIO_PORTC: DDRC = 0xFF;
		     udtReturnValue = E_OK;
		     break;
			 
		case DIO_PORTD: DDRD = 0xFF;
		     udtReturnValue = E_OK; 
		     break;
			 
		default:
			 /*!Comment: Do nothing */
			 break;
		}
		
	}
	else if (u8Direction == DIO_INPUT)
	{
	switch (u8Port)
		{
		case DIO_PORTA: DDRA = 0X00; 
			 udtReturnValue = E_OK;
		     break;
			 
		case DIO_PORTB: DDRB = 0X00;
		     udtReturnValue = E_OK;
		     break;
			 
		case DIO_PORTC: DDRC = 0X00;
		     udtReturnValue = E_OK; 
		     break;
			 
		case DIO_PORTD: DDRD = 0X00;
		     udtReturnValue = E_OK; 
		     break;
			 
		default:
			 /*!Comment: Do nothing */
			 break;
		}
	}
	else
	{
		/*!Comment: Do nothing */
	}
		
	return udtReturnValue;
}

Std_ReturnType DIO_udtSetPortValue
(
	uint8  u8Port,
	uint8  u8Value
)
{
	Std_ReturnType udtReturnValue = E_NOT_OK ;
	switch (u8Port)
		{
		case DIO_PORTA: PORTA = u8Value; 
			 udtReturnValue = E_OK;
		     break;
			 
		case DIO_PORTB: PORTB = u8Value;
		     udtReturnValue = E_OK; 
		     break;
			 
		case DIO_PORTC: PORTC = u8Value;
		     udtReturnValue = E_OK;
		     break;
			 
		case DIO_PORTD: PORTD = u8Value;
		     udtReturnValue = E_OK; 
		     break;
			 
		default:
			 /*!Comment: Do nothing */
			 break;
		}
		return udtReturnValue;	
}

Std_ReturnType DIO_udtGetPortValue 
(
	uint8  u8Port,
	uint8* pu8Value
)
{
	Std_ReturnType udtReturnValue = E_NOT_OK; 
	switch (u8Port)
	{
		case DIO_PORTA: *pu8Value = PINA;
			             udtReturnValue = E_OK; 
			             break;
		case DIO_PORTB: *pu8Value = PINB;
			             udtReturnValue = E_OK; 
			             break;		
		case DIO_PORTC: *pu8Value = PINC; 
					     udtReturnValue = E_OK; 
			             break;
		case DIO_PORTD: *pu8Value = PIND;
			             udtReturnValue = E_OK; 
			             break;
		default:
						 /*!Comment: Do nothing */
						 break;
	}
	return udtReturnValue ;
	
}