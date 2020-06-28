/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
/* Private macro -------------------------------------------------------------*/
#define SELECT_PORT(pinId)                                         ((pinId) / 8)
#define SELECT_PIN(pinId)                                          ((pinId) % 8)
#define NULL 0
#define _L_(pin)                                                            (0u)
#define _H_(pin)                                                      (1<<(pin))
#define _I_(pin)                                                            (0u)
#define _O_(pin)                                                      (1<<(pin))
/* Private functions ---------------------------------------------------------*/
void GPIO_Config()
{
  /**
   * Port Direction ------------------------------------------------------------
   * _O_ - Output
   * _I_ - Input      
   */
  DDRB    =    _O_(7)| _O_(6)| _O_(5)| _O_(4)| _O_(3)| _O_(2)| _O_(1)| _O_(0)  ; 
  DDRC    =    _O_(7)| _O_(6)| _O_(5)| _O_(4)| _O_(3)| _O_(2)| _O_(1)| _O_(0)  ; 
  DDRD    =    _O_(7)| _O_(6)| _O_(5)| _O_(4)| _O_(3)| _O_(2)| _O_(1)| _O_(0)  ;
  
  /**
   * Port value ----------------------------------------------------------------
   *       OUTPUT | INPUT
   * _L_ - Low      Open drain
   * _H_ - High     PullUp
   */
  PORTB   =    _L_(7)| _L_(6)| _L_(5)| _L_(4)| _L_(3)| _L_(2)| _L_(1)| _L_(0)  ;
  PORTC   =    _L_(7)| _L_(6)| _L_(5)| _L_(4)| _L_(3)| _L_(2)| _L_(1)| _L_(0)  ;
  PORTD   =    _L_(7)| _L_(6)| _L_(5)| _L_(4)| _L_(3)| _L_(2)| _L_(1)| _L_(0)  ;
}

void GPIO_PinDirection(pin_et pin, pinDirection_et dir)
{
  uint8_t *directionReg = NULL;
  switch(SELECT_PORT(pin))
  {
#if defined(DDRA)
    case 0:directionReg = (uint8_t*)&DDRA;
           break;
#endif
      
#if defined(DDRB)
    case 1:directionReg = (uint8_t*)&DDRB;
           break;
#endif
      
#if defined(DDRC)
    case 2:directionReg = (uint8_t*)&DDRC;
           break;
#endif
      
#if defined(DDRD)
    case 3: directionReg = (uint8_t*)&DDRD;
            break;
#endif
    default:
      break;
  }
  BIT_Write(*directionReg, SELECT_PIN(pin), dir); 
}

void GPIO_PinWrite(pin_et pin, state_et state)
{
  uint8_t *dataOutReg = NULL;
  switch(SELECT_PORT(pin))
  {
#if defined(PORTA)
    case 0:
      dataOutReg = (uint8_t*)&PORTA;
      break;
#endif

#if defined(PORTB)
    case 1:
      dataOutReg = (uint8_t*)&PORTB;
      break;
#endif
      
#if defined(PORTC)
    case 2:
      dataOutReg = (uint8_t*)&PORTC;
      break;
#endif
      
#if defined(PORTD)
    case 3:
      dataOutReg = (uint8_t*)&PORTD;
      break;
#endif
    default:
      break;
  }
  BIT_Write(*dataOutReg, SELECT_PIN(pin), state);
}

state_et GPIO_PinRead(pin_et pin)
{
  uint8_t *dataInReg = NULL;
  state_et pinState;
  
  switch(SELECT_PORT(pin))
  {
#if defined(PINA)
    case 0:
      dataInReg = (uint8_t*)&PINA;
      break;
#endif

#if defined(PINB)
    case 1:
      dataInReg = (uint8_t*)&PINB;
      break;
#endif
      
#if defined(PINC)
    case 2:
      dataInReg = (uint8_t*)&PINC;
      break;
#endif
      
#if defined(PIND)
    case 3:
      dataInReg = (uint8_t*)&PIND;
      break;
#endif
    default:
      break;
  }
  pinState = BIT_Read(*dataInReg, SELECT_PIN(pin)); 
  return (pinState);
}

void GPIO_PinToggle(pin_et pin)
{
  uint8_t *dataOutReg = NULL;
  switch(SELECT_PORT(pin))
  {
#if defined(PORTA)
    case 0:
      dataOutReg = (uint8_t*)&PORTA;
      break;
#endif

#if defined(PORTB)
    case 1:
      dataOutReg = (uint8_t*)&PORTB;
      break;
#endif
      
#if defined(PORTC)
    case 2:
      dataOutReg = (uint8_t*)&PORTC;
      break;
#endif
      
#if defined(PORTD)
    case 3:
      dataOutReg = (uint8_t*)&PORTD;
      break;
#endif
    default:
      break;
  } 
  BIT_Toggle(*dataOutReg, SELECT_PIN(pin));
}