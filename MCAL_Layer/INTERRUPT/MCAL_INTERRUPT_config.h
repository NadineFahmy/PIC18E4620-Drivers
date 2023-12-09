/* 
 * File:   MCAL_INTERRUPT_config.h
 * Author: Nadine
 *
 * Created on November 20, 2023, 7:01 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/* Section : Include */
#include <xc.h>
//#include <pic18f4620.h>
#include "../MCAL_STD_TYPES.h"
#include "MCAL_INTERRUPT_gen_cfg.h"
#include "../GPIO/HAL_GPIO.h"

/*Section : Macro Declaration */
#define INT_ENABLE               1
#define INT_DISABLE              0

#define INT_OCCUR                1
#define INT_NOT_OCCUR            0

#define INT_PRIORITY_ENABLE      1
#define INT_PRIORITY_DISABLE     0

/*Section : Macro Function Declaration */
#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
#define INT_PRIORITYLevelsEnable()       (RCONbits.IPEN = 1)
#define INT_PRIORITYLevelsDisable()      (RCONbits.IPEN = 0)

#define INT_GlobalInterruptHighEnable()  (INTCONbits.GIEH = 1)
#define INT_GlobalInterruptHighDisable() (INTCONbits.GIEH = 0)

#define INT_GlobalInterruptLowEnable()   (INTCONbits.GIEL = 1)
#define INT_GlobalInterruptLowDisable()  (INTCONbits.GIEL = 0)
#else

#define INT_GlobalInterruptEnable()      (INTCONbits.GIE = 1)
#define INT_GlobalInterruptDisable()     (INTCONbits.GIE = 0)

#define INT_PeripheralInterruptEnable()  (INTCONbits.PEIE = 1)
#define INT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)
#endif

/*Section : Datatype Declaration */
typedef enum {
    INT_LOW_PRIORITY,
    INT_HIGH_PRIORITY
}INT_priority_cfg;

#endif	/* MCAL_INTERRUPT_CONFIG_H */

