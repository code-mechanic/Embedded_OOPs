/* 
 * File:   lcdopps.h
 * Author: Mohan
 *
 * Created on June 6, 2020, 3:17 PM
 */

#ifndef LCDOOPS_H
#define	LCDOOPS_H

#include "gpio.h"

#ifdef	__cplusplus
extern "C" {
#endif
typedef struct
{
    pin_et EN;
    pin_et RS;
    pin_et D4; 
    pin_et D5; 
    pin_et D6; 
    pin_et D7;
}LiquidCrystal_st;

void LCD_Init(LiquidCrystal_st *LCD, pin_et EN, pin_et RS, pin_et D4, pin_et D5, pin_et D6, pin_et D7);
void LCD_String(LiquidCrystal_st *LCD, char *string, uint8_t row, uint8_t pos);
void LCD_Data(LiquidCrystal_st *LCD, uint8_t data);
void LCD_Command(LiquidCrystal_st *LCD, uint8_t cmd);
void LCD_Position(LiquidCrystal_st *LCD, uint8_t row, uint8_t pos);
void LCD_Clear(LiquidCrystal_st *LCD);
#ifdef	__cplusplus
}
#endif

#endif	/* LCDOPPS_H */

