#ifndef _DIO_INTERFACE_H_
#define _DIO_INTERFACE_H_

#define DIO_OUTPUT  ((uint8)0u) 
#define DIO_INPUT   ((uint8)1u)

#define DIO_HIGH    ((uint8)1u)
#define DIO_LOW     ((uint8)0u)

#define DIO_PORTA   ((uint8)0u)
#define DIO_PORTB   ((uint8)1u)
#define DIO_PORTC   ((uint8)2u)
#define DIO_PORTD   ((uint8)3u)

#define DIO_PIN0    ((uint8)0u)
#define DIO_PIN1    ((uint8)1u)
#define DIO_PIN2    ((uint8)2u)
#define DIO_PIN3    ((uint8)3u)
#define DIO_PIN4    ((uint8)4u)
#define DIO_PIN5    ((uint8)5u)
#define DIO_PIN6    ((uint8)6u)
#define DIO_PIN7    ((uint8)7u)



Std_ReturnType DIO_udtSetPinDirection
(
	uint8 u8Port,
	uint8 u8Pin,
	uint8 u8Direction
);

Std_ReturnType DIO_udtSetPinValue
(
	uint8 u8Port,
	uint8 u8Pin,
	uint8 u8Value
);

Std_ReturnType DIO_udtGetPinValue 
(
	uint8  u8Port,
	uint8  u8Pin,
	uint8* pu8Value
);

Std_ReturnType DIO_udtSetPortDirection
(
	uint8  u8Port,
	uint8 u8Direction
);

Std_ReturnType DIO_udtSetPortValue
(
	uint8  u8Port,
	uint8  u8Value
);

Std_ReturnType DIO_udtGetPortValue 
(
	uint8  u8Port,
	uint8* pu8Value
);

#endif 