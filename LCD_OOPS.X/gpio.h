/* 
 * File:   gpio.h
 * Author: Mohan
 *
 * Created on December 25, 2019, 6:37 PM
 */

#ifndef GPIO_H
#define	GPIO_H
/* Includes ------------------------------------------------------------------*/
#include<avr/io.h>
#include "register_access.h"
#ifdef	__cplusplus
extern "C" {
#endif

typedef enum
{
  as_INPUT = 0,
  as_OUTPUT
}pinDirection_et;

typedef enum
{
#ifdef PORTA
  P_A0 =  0U, P_A1, P_A2, P_A3, P_A4, P_A5, P_A6, P_A7,
#endif
#ifdef PORTB
  P_B0 =  8U, P_B1, P_B2, P_B3, P_B4, P_B5, P_B6, P_B7,
#endif
#ifdef PORTC
  P_C0 = 16U, P_C1, P_C2, P_C3, P_C4, P_C5, P_C6, P_C7,
#endif
#ifdef PORTD
  P_D0 = 24U, P_D1, P_D2, P_D3, P_D4, P_D5, P_D6, P_D7,
#endif
}pin_et;

typedef enum{
  LOW = 0,
  HIGH
}state_et;

typedef enum{
  FALSE = 0,
  TRUE
}bool_et;

void GPIO_Config();
void GPIO_PinDirection(pin_et pin, pinDirection_et dir);
void GPIO_PinWrite(pin_et pin, state_et state);
state_et GPIO_PinRead(pin_et pin);
void GPIO_PinToggle(pin_et pin);

#ifdef	__cplusplus
}
#endif

#endif	/* GPIO_H */

