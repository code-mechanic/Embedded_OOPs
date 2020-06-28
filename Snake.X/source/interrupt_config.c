
#include "interrupt_config.h"
/* ########################################################################## */
/*                  EXTERNAL AND PIN CHANGE INTERRUPT SETTING                 */
/* ########################################################################## */

void EXTERNAL_INTERRUPT_config(void)
{
  /**
   * External interrupts ------------------------------------------------------
   * EIMSK
   *   _L_ - Disable
   *   _H_ - Enable
   * EICRC
   *   INT_SENSE_LOW_LEVEL(00)
   *   INT_SENSE_ANY_EDGE(01)
   *   INT_SENSE_FALLING_EDGE(10)
   *   INT_SENSE_RISING_EDGE(11)
   *
   *                    INT1                |              INT0                      
   */
  EIMSK   =            _L_(1)               |             _L_(0)               ;
  EICRA   =   _L_(ISC11)  |   _L_(ISC10)    |   _L_(ISC01)  |   _L_(ISC00)     ; 

  /**
   * Pin change interrupt ------------------------------------------------------
   * PCIRC
   *   _L_ - Disable
   *   _H_ - Enable
   * 
   *              PCIE2      |     PCIE1      |     PCIE0                       
   */
  PCICR   =       _H_(2)     |     _L_(1)     |     _L_(0)                     ;
  
  /**
   * Pin change interrupt channels ---------------------------------------------
   * _L_ - Disable particular pin
   * _H_ - Enable particular pin
   * 
   * PCINT0->|   7   |   6   |   5   |   4   |   3   |   2   |   1   |   0   |
   * PCINT1->|       |   14  |   13  |   12  |   11  |   10  |   9   |   8   |
   * PCINT2->|   23  |   22  |   21  |   20  |   19  |   18  |   17  |   16  |
   */
  PCMSK0  =    _L_(7)| _L_(6)| _L_(5)| _L_(4)| _L_(3)| _L_(2)| _L_(1)| _L_(0)  ;
  PCMSK1  =            _L_(6)| _L_(5)| _L_(4)| _L_(3)| _L_(2)| _L_(1)| _L_(0)  ;
  PCMSK2  =    _L_(7)| _L_(6)| _L_(5)| _H_(4)| _H_(3)| _H_(2)| _H_(1)| _L_(0)  ;
}

