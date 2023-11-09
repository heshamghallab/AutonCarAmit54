#ifndef _LCD_CONFIG_H_
#define _LCD_CONFIG_H_



#define LCD_DATA_PORT            PORTA
#define LCD_DATA_DIRECTION       DDRA

#define LCD_CONTROL_PORT         PORTB
#define LCD_CONTROL_DIRECTION    DDRB

#define LCD_RS                   DIO_PORTB, DIO_PIN1
#define LCD_RW                   DIO_PORTB, DIO_PIN2
#define LCD_E                    DIO_PORTB, DIO_PIN4



#endif