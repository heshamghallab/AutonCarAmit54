#include "STD_TYPES.h"
#include "BIT_MATH.h"

#define F_CPU 16000000UL
#include "util/delay.h"

#include "DIO_interface.h"
#include "DIO_private.h" 

#include "LCD_interface.h" 
#include "LCD_private.h"
#include "LCD_config.h"

Std_ReturnType LCD_udtSendCommand
(
	uint8 u8Command
)
{
	/*!Comment: Clearing RS to send command*/
	DIO_udtSetPinValue(LCD_RS, DIO_LOW);
	
	/*!Comment: Clearing RW to write*/
	DIO_udtSetPinValue(LCD_RW, DIO_LOW);
	
	/*!Comment: Write data on the data port */
	LCD_DATA_PORT = u8Command & 0xF0;
	
	/*!Comment: Enable pusle */
	DIO_udtSetPinValue (LCD_E, DIO_HIGH);
	_delay_us(10);
	DIO_udtSetPinValue (LCD_E, DIO_LOW);
	_delay_us(100);
	/*!Comment: Write data on the data port */
	LCD_DATA_PORT = u8Command << 4 ;
	
	/*!Comment: Enable pusle */
	DIO_udtSetPinValue (LCD_E, DIO_HIGH);
	_delay_us(10);
	DIO_udtSetPinValue (LCD_E, DIO_LOW);
	_delay_us(100);

}

Std_ReturnType LCD_udtSendData
(
	uint8 u8Data
)
{
	/*!Comment: setting RS to send data*/
	DIO_udtSetPinValue(LCD_RS, DIO_HIGH);
	
	/*!Comment: Clearing RW to write*/
	DIO_udtSetPinValue(LCD_RW, DIO_LOW);
	
	/*!Comment: Write data on the data port */
	LCD_DATA_PORT = u8Data & 0xF0;
	
	/*!Comment: Enable pusle */
	DIO_udtSetPinValue (LCD_E, DIO_HIGH);
	_delay_us(10);
	DIO_udtSetPinValue (LCD_E, DIO_LOW);
	_delay_us(100);

	/*!Comment: Write data on the data port */
	LCD_DATA_PORT = u8Data << 4 ;
	
	/*!Comment: Enable pusle */
	DIO_udtSetPinValue (LCD_E, DIO_HIGH);
	_delay_us(10);
	DIO_udtSetPinValue (LCD_E, DIO_LOW);
	_delay_us(100);

}

void LCD_vidInit
(
	void
)
{
	LCD_DATA_DIRECTION = 0xFF;
	
	DIO_udtSetPinDirection(LCD_RS,DIO_OUTPUT);
	DIO_udtSetPinDirection(LCD_RW,DIO_OUTPUT);
	DIO_udtSetPinDirection(LCD_E,DIO_OUTPUT);
	
	 /* _delay_ms(40);
	 
	LCD_udtSendCommand(0x22);
	LCD_udtSendCommand(0x80);
	_delay_ms(1);
	LCD_udtSendCommand(0x0F);

	_delay_ms(1);
	
	LCD_udtSendCommand(0x01);
	
	_delay_ms(2);
	
	LCD_udtSendCommand(0x06); */ 
	
	_delay_ms(40);
	LCD_udtSendCommand(0x33);
	LCD_udtSendCommand(0x32);
	LCD_udtSendCommand(0x28);
	_delay_ms(1);
	LCD_udtSendCommand(0x0F);
	_delay_ms(1);
	LCD_udtSendCommand(0x01);
	_delay_ms(2);
	LCD_udtSendCommand(0x06);


	
	 
	/* _delay_ms(40);
	 LCD_udtSendCommand(0x30);
	 _delay_ms(10);
	 LCD_udtSendCommand(0x03);
	 _delay_us(500);
	 LCD_udtSendCommand(0x32);
	 LCD_udtSendCommand(0x26);
	 LCD_udtSendCommand(0x08);
	 LCD_udtSendCommand(0x01);
	 LCD_udtSendCommand(0x03);*/
}

Std_ReturnType LCD_udtPrint
(
	uint8 u8Print[16]
)
{
	LCD_udtSendCommand(0x01);
	_delay_ms(100);
	
	uint8 i=0;
	for( i=0 ; u8Print[i] != '\0' ; i++)
	{
		LCD_udtSendData(u8Print[i]);
	}
}

void LCD_vidPrintWord (uint8* pu8Word ) 
{
	
	uint8 u8Counter = 0; 
	while (pu8Word[u8Counter] != '\0')
	{
		LCD_udtSendData(pu8Word[u8Counter++]);
	}	
}

void LCD_vidGoTo
(
	uint8 u8Row,
	uint8 u8Column
 )
{
	if ( u8Row == 0 )
	{
		LCD_udtSendCommand(u8Column + 128);
	}
	else
	{
		LCD_udtSendCommand((u8Column+0x40) + 128 );
	}
}

void LCD_vidSpecialChar
(
	uint8 *pu8Arr,
	uint8 u8CGRAMLocation,
	uint8 u8Row,
	uint8 u8Column
)
{
	uint8 u8Counter;
	
	LCD_udtSendCommand((u8CGRAMLocation*8)+64);
	
	for ( u8Counter = 0 ; u8Counter <8 ; u8Counter++)
	{
		LCD_udtSendData(pu8Arr[u8Counter]);
	}
	/* go back to DDRAM */
	LCD_vidGoTo (u8Row , u8Column );
	
	/*print CGRAM location u8CGRAMLocation data */

	LCD_udtSendData (u8CGRAMLocation);
}


