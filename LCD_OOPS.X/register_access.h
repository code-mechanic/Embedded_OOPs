/* 
 * File:   register_access.h
 * Author: Mohan
 *
 * Created on December 25, 2019, 6:20 PM
 */
#ifndef REGISTER_ACCESS_H
#define REGISTER_ACCESS_H

#ifdef __cplusplus
 extern "C" {
#endif

/*Macro Function ------------------------------------------------------------*/
#define BIT_Mask(bitpos)                                        (1 << (bitpos))
#define BIT_Set(reg, bitpos)                     ((reg) |=  BIT_Mask((bitpos)))
#define BIT_Clear(reg, bitpos)                   ((reg) &= ~BIT_Mask((bitpos)))
#define BIT_Read(reg, bitpos)                      (((reg) >> (bitpos)) & 0x1U)
#define BIT_Toggle(reg, bitpos)                  ((reg) ^=  BIT_Mask((bitpos)))
#define BIT_Write(reg, bitpos, val)                                           \
                ((val) ? BIT_Set((reg), (bitpos)) : BIT_Clear((reg), (bitpos)))
     
#define BIT_IsSet(reg, bitpos)                      (BIT_Read((reg), (bitpos)))
#define BIT_IsClear(reg, bitpos)            (BIT_Read((reg), (bitpos)) == 0x0U)

#ifdef __cplusplus
}
#endif

#endif /* REGISTER_ACCESS_H */
