/* 
 * File:   HAL_TIMER3.h
 * Author: yoga
 *
 * Created on November 25, 2023, 6:37 PM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/* Section : Include */
#include <xc.h>
//#include <pic18f4620.h>
#include "../MCAL_STD_TYPES.h"
#include "../GPIO/HAL_GPIO.h"
#include "../INTERRUPT/MCAL_INTERNAL_INTERRUPT.h"

/*Section : Macro Declaration */
#define TIMER3_TIMER_MODE   0
#define TIMER3_COUNTER_MODE 1

#define TIMER3_ASYNC_COUNTER_MODE   1
#define TIMER3_SYNC_COUNTER_MODE    0

#define TIMER3_PRESCALER_DIV_BY_1 0
#define TIMER3_PRESCALER_DIV_BY_2 1
#define TIMER3_PRESCALER_DIV_BY_4 2
#define TIMER3_PRESCALER_DIV_BY_8 3

#define TIMER3_RW_REG_8BIT_MODE   0
#define TIMER3_RW_REG_16BIT_MODE  1

/*Section : Macro Function Declaration */
#define TIMER3_MODULE_ENABLE()      (T3CONbits.TMR3ON = 1)
#define TIMER3_MODULE_DISABLE()     (T3CONbits.TMR3ON = 0)

#define TIMER3_TIMER_MODE_ENABLE()     (T3CONbits.TMR3CS = 0)
#define TIMER3_COUNTER_MODE_ENABLE()   (T3CONbits.TMR3CS = 1)

#define TIMER3_ASYNC_COUNTER_MODE_ENABLE()   (T3CONbits.T3SYNC = 1)
#define TIMER3_SYNC_COUNTER_MODE_ENABLE()    (T3CONbits.T3SYNC = 0)

#define TIMER3_PRESCALER_SELECT(_PRESCALER_)  (T3CONbits.T3CKPS = _PRESCALER_)

#define TIMER3_RW_8BIT_REG_MODE_ENABLE()      (T3CONbits.RD16 = 0)
#define TIMER3_RW_16BIT_REG_MODE_ENABLE()     (T3CONbits.RD16 = 1)

/*Section : Datatype Declaration */
typedef struct {
#if TMR3_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
    void(* TMR3_InterruptHandler)(void);
    INT_priority_cfg priority;
#endif
    u16 timer3_preload_value;
    u8 timer3_prescaler_value: 2 ;
    u8 timer3_counter_mode: 1 ;
    u8 timer3_mode: 1 ;;
    u8 timer3_reg_rw_mode: 1 ;
    u8 timer3_reserved: 3 ;    
}timer3_t;

/*Section : Function Declaration */
Std_ReturnType TMR3_Inti(const timer3_t *_timer);
Std_ReturnType TMR3_DeInti(const timer3_t *_timer);
Std_ReturnType TMR3_Write_Value(const timer3_t *_timer, u16 _value);
Std_ReturnType TMR3_Read_Value(const timer3_t *_timer, u16 *_value);


#endif	/* HAL_TIMER3_H */

