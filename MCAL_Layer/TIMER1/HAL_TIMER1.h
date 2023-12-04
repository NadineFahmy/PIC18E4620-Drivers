/* 
 * File:   HAL_TIMER1.h
 * Author: Nadine
 *
 * Created on November 25, 2023, 1:31 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/* Section : Include */
#include <xc.h>
//#include <pic18f4620.h>
#include "../MCAL_STD_TYPES.h"
#include "../GPIO/HAL_GPIO.h"
#include "../INTERRUPT/MCAL_INTERNAL_INTERRUPT.h"

/*Section : Macro Declaration */
#define TIMER1_TIMER_MODE   0
#define TIMER1_COUNTER_MODE 1

#define TIMER1_ASYNC_COUNTER_MODE   1
#define TIMER1_SYNC_COUNTER_MODE    0

#define TIMER1_OSC_ENABLE  1
#define TIMER1_OSC_DISABLE 0

#define TIMER1_PRESCALER_DIV_BY_1 0
#define TIMER1_PRESCALER_DIV_BY_2 1
#define TIMER1_PRESCALER_DIV_BY_4 2
#define TIMER1_PRESCALER_DIV_BY_8 3

#define TIMER1_RW_REG_8BIT_MODE   0
#define TIMER1_RW_REG_16BIT_MODE  1

/*Section : Macro Function Declaration */
#define TIMER1_PRESCALER_SELECT(_PRESCALER_)  (T1CONbits.T1CKPS = _PRESCALER_)

#define TIMER1_TIMER_MODE_ENABLE()     (T1CONbits.TMR1CS = 0)
#define TIMER1_COUNTER_MODE_ENABLE()   (T1CONbits.TMR1CS = 1)

#define TIMER1_ASYNC_COUNTER_MODE_ENABLE()   (T1CONbits.T1SYNC = 1)
#define TIMER1_SYNC_COUNTER_MODE_ENABLE()    (T1CONbits.T1SYNC = 0)

#define TIMER1_OSC_HW_ENABLE  (T1CONbits.T1OSCEN = 1)
#define TIMER1_OSC_HW_DISABLE (T1CONbits.T1OSCEN = 0)

#define TIMER1_RW_8BIT_REG_MODE_ENABLE()      (T1CONbits.RD16 = 0)
#define TIMER1_RW_16BIT_REG_MODE_ENABLE()     (T1CONbits.RD16 = 1)

#define TIMER1_MODULE_ENABLE()      (T1CONbits.TMR1ON = 1)
#define TIMER1_MODULE_DISABLE()     (T1CONbits.TMR1ON = 0)

#define TIMER1_SYSTEM_CLK_STATUS()      (T1CONbits.T1RUN)

/*Section : Datatype Declaration */
typedef struct {
#if TMR1_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
    void(* TMR1_InterruptHandler)(void);
    INT_priority_cfg priority;
#endif
    u16 timer1_preload_value;
    u8 timer1_prescaler_value: 2 ;
    u8 timer1_mode: 1 ;
    u8 timer1_counter_mode: 1 ;
    u8 timer1_osc_cfg: 1 ;
    u8 timer1_reg_rw_mode: 1 ;
    u8 timer1_reserved: 2 ;    
}timer1_t;

/*Section : Function Declaration */
Std_ReturnType TMR1_Inti(const timer1_t *_timer);
Std_ReturnType TMR1_DeInti(const timer1_t *_timer);
Std_ReturnType TMR1_Write_Value(const timer1_t *_timer, u16 _value);
Std_ReturnType TMR1_Read_Value(const timer1_t *_timer, u16 *_value);

#endif	/* HAL_TIMER1_H */

