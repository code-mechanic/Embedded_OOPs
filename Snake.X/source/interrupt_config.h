/* 
 * File:   interrupt_config.h
 * Author: Mohan
 *
 * Created on June 28, 2020, 9:37 AM
 */

#ifndef INTERRUPT_CONFIG_H
#define	INTERRUPT_CONFIG_H
#include <avr/interrupt.h>
#ifdef	__cplusplus
extern "C" {
#endif

#define _L_(pin)                                                            (0u)
#define _H_(pin)                                                      (1<<(pin))
#define _I_(pin)                                                            (0u)
#define _O_(pin)                                                      (1<<(pin))

#define MCU_INTERRUPT_ENABLE()                                             sei()
#define MCU_INTERRUPT_DISABLE()                                            cli()

void EXTERNAL_INTERRUPT_config(void);

#ifdef	__cplusplus
}
#endif

#endif	/* INTERRUPT_CONFIG_H */

