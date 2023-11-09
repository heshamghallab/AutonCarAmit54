#ifndef _TIMER1_PRIVATE_H_
#define _TIMER1_PRIVATE_H_


#define TCCR1A   *((uint8*)0x4Fu)
#define TCCR1B   *((uint8*)0x4Eu)
#define TCNT1    *((uint16*)0x4Cu)
#define OCR1A    *((uint16*)0x4Au)
#define OCR1B    *((uint16*)0x48u)
#define ICR1     *((uint16*)0x46u)
#define TIMSK1   *((uint8*)0x59u)
#define TIFR1    *((uint8*)0x58u)


#endif