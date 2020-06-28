/*
 * File:   main.c
 * Author: Mohan
 *
 * Created on June 26, 2020, 1:40 PM
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcdoops.h"
#include "gamestatemachine.h"
#include "interrupt_config.h"

int main(void) {
  MCU_INTERRUPT_ENABLE();
  EXTERNAL_INTERRUPT_config();
  Game_Setup();
  
  init:
  Game_Init();
  while(1)
  {
    if(Game_Execute())
    {
      goto init;
    }
  }
}
