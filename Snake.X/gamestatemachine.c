#define F_CPU 16000000UL

/*--------------------------------Includes------------------------------------*/
#include "gamestatemachine.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <time.h>

/*-------------------------Macros and Type definitions------------------------*/
#define F_ROW 4
#define F_COL 20

typedef struct
{
  int X;
  int Y;
}Coordinate_st;
/*-----------------------------Global Declaration-----------------------------*/

struct dir
{
  char up;
  char down;
  char left;
  char right;
}Direction;

char field_map[F_ROW][F_COL];
/*In field map   0 indicate empty space
 *               1 indicate tail
 * other numerical indicate body
 *   Max numerical indicate Head
 *             'f' indicate food
 */
unsigned int snake_length;
Coordinate_st Snake_pos, Food_pos;
int isfood_Available;
char prev_dir;
char Head, Tail;
char Score;
char isError;

/*--------------------------Global Initialization-----------------------------*/
char Highscore = 0;

/*----------------------------Private Functions-------------------------------*/
char Check_for_Error()
{
  if((field_map[Snake_pos.X][Snake_pos.Y] != 0) && (field_map[Snake_pos.X][Snake_pos.Y] != 'f'))
  {
    return 1;
  }
  return 0;
}

void generate_food()
{
  redo:
  Food_pos.X = rand() % 4;
  Food_pos.Y = rand() % 16;
  if(field_map[Food_pos.X][Food_pos.Y] == 0 )
  {
    field_map[Food_pos.X][Food_pos.Y] = 'f';
    isfood_Available = 1;
  }
  else
  {
    goto redo;
  }
}

int Check_for_food()
{
  if(field_map[Snake_pos.X][Snake_pos.Y] == 'f')
  {
    isfood_Available = 0;
    Score = Score+5;
    snake_length++;
    LCD_Number(&Score_board, Score, 0, 12);
    LCD_Number(&Score_board_1, snake_length, 0, 13);
    GPIO_PinWrite(P_C5, HIGH);
    _delay_ms(100);
    GPIO_PinWrite(P_C5, LOW);
    return 0;
  }
  return 1;
}

void Srink_Tail()
{
  for(int i=0; i<F_ROW; i++)
  {
    for(int j=0; j<F_COL; j++)
    {
      if(field_map[i][j] == Tail)
      {
        field_map[i][j] = 0;
        goto exit;
      }
    }
  }
  exit:
  Tail++;
}

void Movement()
{
  if(Direction.up)
  {
    (Snake_pos.X)--;
    if((Snake_pos.X) == -1) Snake_pos.X = F_ROW-1;
  }
  else if(Direction.right)
  {
    (Snake_pos.Y)++;
    if((Snake_pos.Y) == F_COL) Snake_pos.Y = 0; 
  }
  else if(Direction.left)
  {
    (Snake_pos.Y)--;
    if((Snake_pos.Y) == -1) Snake_pos.Y = F_COL-1;   
  }
  else if(Direction.down)
  {
    (Snake_pos.X)++;
    if((Snake_pos.X) == F_ROW) Snake_pos.X = 0;
  }
  if(Check_for_Error())
  {
    isError = 1;
    return;
  }
  if(Check_for_food())
  {
    Srink_Tail(); 
  }
  Head++;
  field_map[Snake_pos.X][Snake_pos.Y] = Head; 
}

void Print_Snake()
{
  for(int i=0; i<F_ROW; i++)
  {
    for(int j=0; j<F_COL; j++)
    {
      if(field_map[i][j] == Head)
        LCD_String(&Field, "O", i, j);
      else if((field_map[i][j] > 0) && (field_map[i][j] != Head) && (field_map[i][j] != 'f'))
        LCD_String(&Field, "o", i, j);
      else if(field_map[i][j] == 'f')
        LCD_String(&Field, "F", i, j);
    }
  }
}
/*-----------------------------Public Functions-------------------------------*/

void Game_Setup()
{
  /*---------------------HardWare setup for the Game--------------------------*/
  LCD_Init(&Field, P_C1, P_B1, P_B2, P_B3, P_B4, P_B5);
  LCD_Init(&Score_board, P_B0, P_B1, P_B2, P_B3, P_B4, P_B5);
  LCD_Init(&Score_board_1, P_C0, P_B1, P_B2, P_B3, P_B4, P_B5);
  GPIO_PinDirection(P_D0, as_INPUT); //OK BUTTON(PULL-DOWN)
  GPIO_PinDirection(P_D1, as_INPUT); //UP BUTTON(PULL-UP)
  GPIO_PinDirection(P_D2, as_INPUT); //RIGHT BUTTON(PULL-UP))
  GPIO_PinDirection(P_D3, as_INPUT); //LEFT BUTTON(PULL-UP)
  GPIO_PinDirection(P_D4, as_INPUT); //DOWN BUTTON(PULL-UP)
  GPIO_PinDirection(P_C5, as_OUTPUT); // LED
}

void Game_Init()
{
  for(int i=0; i<F_ROW; i++)
    for(int j=0; j<F_COL; j++)
      field_map[i][j] = 0;
  /*----------------------------------------------------------------------------
   * Initial Position, Snake length, Scores, Error flag and food count        */
  Snake_pos.X = F_ROW/2;  
  Snake_pos.Y = F_COL/2;  
  Head = 2;
  Tail = 1;
  snake_length = 2;
  Score = 0;
  isfood_Available = 0;
  isError = 0;
  /*----------------------------------------------------------------------------
   * Setting the Snake body in Initial position                               */
  int temp_Y = Snake_pos.Y;
  for(int i=0; i<Head; i++)
  {
    temp_Y++;
    field_map[Snake_pos.X][temp_Y - Head] = i+1;
  }
  /*----------------------------------------------------------------------------
   * Setting Initial Direction                                                */
  Direction.up = 0;
  Direction.down = 0;
  Direction.left = 0;
  Direction.right = 1;
  prev_dir = 'r';
  /*----------------------------------------------------------------------------
   * Menu Option in LCD                                                       */
  LCD_Clear(&Score_board);
  LCD_Clear(&Field);
  LCD_Clear(&Score_board_1);
  LCD_String(&Score_board, "SCORE     :", 0,0);
  LCD_Number(&Score_board, Score, 0, 12);
  LCD_String(&Score_board, "HIGH SCORE:", 1,0);
  LCD_Number(&Score_board, Highscore, 1, 12);
  LCD_String(&Score_board_1, "SNAKE LENGTH:", 0,0);
  LCD_Number(&Score_board_1, snake_length, 0, 13);
  LCD_String(&Field, "SNAKE GAME", 0, 5);
  LCD_String(&Field, "Press OK button", 2, 3);
  LCD_String(&Field, "to Start", 3, 6);
  while(!GPIO_PinRead(P_D0));
  /*--------------------------------------------------------------------------*/
}

char Game_Execute()
{
  LCD_Clear(&Field);
  if(!isfood_Available)
  {
    generate_food();
  }
  Movement();
  Print_Snake();
  if(isError)
  {
    LCD_Clear(&Field);
    LCD_String(&Field, "GAME OVER!", 0, 5);
    if(Score > Highscore)
    {
      LCD_String(&Field, "NEW HIGH SCORE!", 2, 3);
      Highscore = Score;
    }
    _delay_ms(1000);
    return 1;
  }
  _delay_ms(400);
  return 0;
}

/*-----------------------------Interrupt Routines-----------------------------*/
ISR(PCINT2_vect)
{
  if(!GPIO_PinRead(P_D1) && (prev_dir != 'd'))
  {
    Direction.up = 1;
    Direction.down = 0;
    Direction.left = 0;
    Direction.right = 0;
    prev_dir = 'u';
  }
  if(!GPIO_PinRead(P_D2) && (prev_dir != 'l'))
  {
    Direction.up = 0;
    Direction.down = 0;
    Direction.left = 0;
    Direction.right = 1;
    prev_dir = 'r';
  }
  if(!GPIO_PinRead(P_D3) && (prev_dir != 'r'))
  {
    Direction.up = 0;
    Direction.down = 0;
    Direction.left = 1;
    Direction.right = 0;
    prev_dir = 'l';
  }
  if(!GPIO_PinRead(P_D4) && (prev_dir != 'u'))
  {
    Direction.up = 0;
    Direction.down = 1;
    Direction.left = 0;
    Direction.right = 0;
    prev_dir = 'd';
  }
}
