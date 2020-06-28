/* 
 * File:   gamestatemachine.h
 * Author: Mohan
 *
 * Created on June 26, 2020, 2:16 PM
 */

#ifndef GAMESTATEMACHINE_H
#define	GAMESTATEMACHINE_H

#include "lcdoops.h"
#include "gpio.h"
#ifdef	__cplusplus
extern "C" {
#endif
    
LiquidCrystal_st Field;
LiquidCrystal_st Score_board;
LiquidCrystal_st Score_board_1;

void Game_Setup();
void Game_Init();
char Game_Execute();


#ifdef	__cplusplus
}
#endif

#endif	/* GAMESTATEMACHINE_H */

