#ifndef _BIT_MATH_H_
#define _BIT_MATH_H_ 

#define SET_BIT(var, bit) var |=  (1<<bit)
#define CLR_BIT(var, bit) var &= ~(1<<bit)
#define GET_BIT(var, bit) ((var>>bit)&1)
#define TOG_BIT(var, bit) var ^=  (1<<bit)


#endif