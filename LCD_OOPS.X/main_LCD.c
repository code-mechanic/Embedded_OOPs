 /*
 * File:   main_LCD.c
 * Author: Mohan
 *
 * Created on June 6, 2020, 2:54 PM
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcdoops.h"
#include "gpio.h"

int main(void) 
{
  GPIO_PinDirection(P_D0,as_INPUT);
  GPIO_PinDirection(P_D1,as_INPUT);
  LiquidCrystal_st LCD1;
  LiquidCrystal_st LCD2;
  LiquidCrystal_st LCD3;
  LCD_Init(&LCD1,P_B0,P_B1,P_B2,P_B3,P_B4,P_B5);
  LCD_Init(&LCD2,P_C0,P_B1,P_B2,P_B3,P_B4,P_B5);
  LCD_Init(&LCD3,P_C1,P_B1,P_B2,P_B3,P_B4,P_B5);
  while(1)
  {
    LCD_String(&LCD1, "LCD NO:1", 0, 4);
    LCD_String(&LCD1, "HELLO", 1, 0);
    LCD_String(&LCD2, "LCD NO:2", 0, 4);
    LCD_String(&LCD2, "WORLD", 1, 0);
    LCD_String(&LCD3, "0123456789012345", 0, 0);
    LCD_String(&LCD3, "ABCDEFGHIJKLMNOP", 1, 0);
    LCD_String(&LCD3, "abcdefghijklmnop", 2, 0);
    LCD_String(&LCD3, "AbCdEfGhIjKlMnOp", 3, 0);
    _delay_ms(1000);
    LCD_Clear(&LCD1);
    LCD_Clear(&LCD2);
    LCD_Clear(&LCD3);
    _delay_ms(500);
  }
}
