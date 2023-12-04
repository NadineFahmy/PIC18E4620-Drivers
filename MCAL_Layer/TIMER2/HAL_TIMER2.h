/* 
 * File:   HAL_TIMER2.h
 * Author: 
 *
 * Created on November 25, 2023, 6:31 PM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/* Section : Include */
#include <xc.h>
//#include <pic18f4620.h>
#include "../MCAL_STD_TYPES.h"
#include "../GPIO/HAL_GPIO.h"
#include "../INTERRUPT/MCAL_INTERNAL_INTERRUPT.h"

/*Section : Macro Declaration */
#define TIMER2_POSTSCALER_DIV_BY_1  0
#define TIMER2_POSTSCALER_DIV_BY_2  1
#define TIMER2_POSTSCALER_DIV_BY_3  2
#define TIMER2_POSTSCALER_DIV_BY_4  3
#define TIMER2_POSTSCALER_DIV_BY_5  4
#define TIMER2_POSTSCALER_DIV_BY_6  5
#define TIMER2_POSTSCALER_DIV_BY_7  6
#define TIMER2_POSTSCALER_DIV_BY_8  7
#define TIMER2_POSTSCALER_DIV_BY_9  8
#define TIMER2_POSTSCALER_DIV_BY_10 9
#define TIMER2_POSTSCALER_DIV_BY_11 10
#define TIMER2_POSTSCALER_DIV_BY_12 11
#define TIMER2_POSTSCALER_DIV_BY_13 12
#define TIMER2_POSTSCALER_DIV_BY_14 13
#define TIMER2_POSTSCALER_DIV_BY_15 15
#define TIMER2_POSTSCALER_DIV_BY_16 16

#define TIMER2_PRESCALER_DIV_BY_1  0
#define TIMER2_PRESCALER_DIV_BY_4  1
#define TIMER2_PRESCALER_DIV_BY_16  2

/*Section : Macro Function Declaration */
#define TIMER2_MODULE_ENABLE()      (T2CONbits.TMR2ON = 1)
#define TIMER2_MODULE_DISABLE()     (T2CONbits.TMR2ON = 0)

#define TIMER2_PRESCALER_SELECT(_PRESCALER_)  (T2CONbits.T2CKPS = _PRESCALER_)

#define TIMER2_POSTSCALER_SELECT(_POSTSCALER_)  (T2CONbits.TOUTPS = _POSTSCALER_)

/*Section : Datatype Declaration */
typedef struct {
#if TMR2_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
    void(* TMR2_InterruptHandler)(void);
    INT_priority_cfg priority;
#endif
    u8 timer2_postscaler_value: 4;
    u8 timer2_prescaler_value: 2;
    u8 timer2_preload_value;
    u8 timer2_reserved: 2 ;    
}timer2_t;

/*Section : Function Declaration */
Std_ReturnType TMR2_Inti(const timer2_t *_timer);
Std_ReturnType TMR2_DeInti(const timer2_t *_timer);
Std_ReturnType TMR2_Write_Value(const timer2_t *_timer, u8 _value);
Std_ReturnType TMR2_Read_Value(const timer2_t *_timer, u8 *_value);

#endif	/* HAL_TIMER2_H */

