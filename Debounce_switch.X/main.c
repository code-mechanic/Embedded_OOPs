/*
 * File:   main.c
 * Author: Mohan
 *
 * Created on June 29, 2020, 8:36 AM
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include "gpio.h"
#include <util/delay.h>
#include "interrupt_config.h"

char Handle_debounce(char state);
char pressed = 0;

int main(void) {
  MCU_INTERRUPT_ENABLE();
  EXTERNAL_INTERRUPT_config();
  //char Pinstate = 0;
  GPIO_PinDirection(P_B0, as_INPUT);
  GPIO_PinDirection(P_B1, as_OUTPUT);
  while(1)
  {
    /*Method 1:
     * In case of input is given over long period but this seldom works*/
    /*if(GPIO_PinRead(P_B0))
    {
      while(GPIO_PinRead(P_B0)); 
      pressed++;
    }*/
    
    /*Method 2:
     * In case of input is given rapidly then De-bounce is avoid by small delay.
     * Duration of delay depends on De-bounce of mechanical switch.*/
    /*if(GPIO_PinRead(P_B0))
    {
      _delay_ms(200);            
      pressed++;
    }*/
    
    /*Method 3:
     * This can handle long period and rapid press, perfectly handle De-bounce*/
    /*if(Handle_debounce(Pinstate) && Pinstate == 0)
    {
      Pinstate = 1;
      pressed++;
    }
    else if(!Handle_debounce(Pinstate) && Pinstate == 1)
    {
      Pinstate = 0;
    }*/
    if(pressed == 10)
    {
      GPIO_PinToggle(P_B1);
      pressed = 0;
    }
  }
}

ISR(INT0_vect)
{
  _delay_ms(30);
  pressed++;
}
char Handle_debounce(char state)
{
  static char current_state;
  current_state = GPIO_PinRead(P_B0);
  if(state != current_state)
  {
    _delay_ms(10);
    current_state = GPIO_PinRead(P_B0);
  }
  return current_state;
}