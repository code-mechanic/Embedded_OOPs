
#define F_CPU 16000000UL
#include "lcdoops.h"
#include <util/delay.h>
#include <math.h>

void LCD_Init(LiquidCrystal_st *LCD, pin_et EN, pin_et RS, pin_et D4, pin_et D5, pin_et D6, pin_et D7)
{
  LCD->EN = EN;
  LCD->RS = RS;
  LCD->D4 = D4;
  LCD->D5 = D5;
  LCD->D6 = D6;
  LCD->D7 = D7;
  GPIO_PinDirection(LCD->EN,as_OUTPUT);
  GPIO_PinDirection(LCD->RS,as_OUTPUT);
  GPIO_PinDirection(LCD->D4,as_OUTPUT);
  GPIO_PinDirection(LCD->D5,as_OUTPUT);
  GPIO_PinDirection(LCD->D6,as_OUTPUT);
  GPIO_PinDirection(LCD->D7,as_OUTPUT);
  LCD_Command(LCD, 0x02);
  LCD_Command(LCD, 0x28);
  LCD_Command(LCD, 0x0C);
  LCD_Command(LCD, 0x06);
  LCD_Command(LCD, 0x01);
  LCD_Command(LCD, 0x80);
}

void LCD_Command(LiquidCrystal_st *LCD, uint8_t cmd)
{
  GPIO_PinWrite(LCD->D4,cmd&16);
  GPIO_PinWrite(LCD->D5,cmd&32);
  GPIO_PinWrite(LCD->D6,cmd&64);
  GPIO_PinWrite(LCD->D7,cmd&128);
  
  GPIO_PinWrite(LCD->RS,LOW);
  GPIO_PinWrite(LCD->EN,HIGH);
  _delay_us(10);
  GPIO_PinWrite(LCD->EN,LOW);
  _delay_ms(10);
  
  GPIO_PinWrite(LCD->D4,cmd&1);
  GPIO_PinWrite(LCD->D5,cmd&2);
  GPIO_PinWrite(LCD->D6,cmd&4);
  GPIO_PinWrite(LCD->D7,cmd&8);
  
  GPIO_PinWrite(LCD->RS,LOW);
  GPIO_PinWrite(LCD->EN,HIGH);
  _delay_us(10);
  GPIO_PinWrite(LCD->EN,LOW);
  _delay_ms(10);
}

void LCD_Data(LiquidCrystal_st *LCD, uint8_t data)
{
  GPIO_PinWrite(LCD->D4,data&16);
  GPIO_PinWrite(LCD->D5,data&32);
  GPIO_PinWrite(LCD->D6,data&64);
  GPIO_PinWrite(LCD->D7,data&128);
  
  GPIO_PinWrite(LCD->RS,HIGH);
  GPIO_PinWrite(LCD->EN,HIGH);
  _delay_us(10);
  GPIO_PinWrite(LCD->EN,LOW);
  
  GPIO_PinWrite(LCD->D4,data&1);
  GPIO_PinWrite(LCD->D5,data&2);
  GPIO_PinWrite(LCD->D6,data&4);
  GPIO_PinWrite(LCD->D7,data&8);
  
  GPIO_PinWrite(LCD->RS,HIGH);
  GPIO_PinWrite(LCD->EN,HIGH);
  _delay_us(10);
  GPIO_PinWrite(LCD->EN,LOW);
  _delay_ms(10);
}

void LCD_Position(LiquidCrystal_st *LCD, uint8_t row, uint8_t pos)
{
  if(row == 0)
  {
    LCD_Command(LCD,(pos + 0x80));
  }
  else if(row == 1)
  {
    LCD_Command(LCD,(pos + 0xC0));
  }
  else if(row == 2)
  {
    LCD_Command(LCD,(pos + 0x94));
  }
  else if(row == 3)
  {
    LCD_Command(LCD, (pos + 0xD4));
  }
}
void LCD_String(LiquidCrystal_st *LCD, char *string, uint8_t row, uint8_t pos)
{
  LCD_Position(LCD,row,pos);
  while(*string)
  {
    LCD_Data(LCD,*string);
    string++;
  }
}

void LCD_Clear(LiquidCrystal_st *LCD)
{
  LCD_Command(LCD,0x01);
}