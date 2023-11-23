/* 
 * File:   HAL_TIMER0.h
 * Author: Nadine
 *
 * Created on November 23, 2023, 7:58 PM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/* Section : Include */
#include <xc.h>
//#include <pic18f4620.h>
#include "../MCAL_STD_TYPES.h"
#include "../GPIO/HAL_GPIO.h"
#include "../INTERRUPT/MCAL_INTERNAL_INTERRUPT.h"

/*Section : Macro Declaration */
#define TIMER0_PRESCALER_ENABLE_CFG  1
#define TIMER0_PRESCALER_DISABLE_CFG 0

#define TIMER0_RISING_EDGE_CFG  1
#define TIMER0_FALLING_EDGE_CFG 0

#define TIMER0_TIMER_MODE   1
#define TIMER0_COUNTER_MODE 0

#define TIMER0_8BIT_REGISTER_MODE   1
#define TIMER0_16BIT_REGISTER_MODE  0

/*Section : Macro Function Declaration */
#define TIMER0_PRESCALER_ENABLE()  (T0CONbits.PSA = 0)
#define TIMER0_PRESCALER_DISABLE() (T0CONbits.PSA = 1)

#define TIMER0_RISING_EDGE_ENABLE()   (T0CONbits.T0SE = 0)
#define TIMER0_FALLING_EDGE_ENABLE()  (T0CONbits.T0SE = 1)

#define TIMER0_TIMER_MODE_ENABLE()     (T0CONbits.T0CS = 0)
#define TIMER0_COUNTER_MODE_ENABLE()   (T0CONbits.T0CS = 1)

#define TIMER0_8BIT_REGISTER_MODE_ENABLE()      (T0CONbits.T08BIT = 1)
#define TIMER0_16BIT_REGISTER_MODE_ENABLE()     (T0CONbits.T08BIT = 0)

#define TIMER0_MODULE_ENABLE()      (T0CONbits.TMR0ON = 1)
#define TIMER0_MODULE_DISABLE()     (T0CONbits.TMR0ON = 0)

/*Section : Datatype Declaration */
typedef enum{
    TIMER0_PRESCALER_DIV_BY_2,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_16,
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256,
}timer0_prescaler_select_t;

typedef struct {
#if TMR0_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
    void(* TMR0_InterruptHandler)(void);
    INT_priority_cfg priority;
#endif
    u16 timer0_preload_value;
    timer0_prescaler_select_t  prescaler_value;
    u8 prescaler_enable: 1 ;
    u8 timer0_counter_edge: 1 ;
    u8 timer0_mode: 1 ;
    u8 timer0_register_size: 1 ;
    u8 timer0_reserved: 4 ;    
}timer0_t;

/*Section : Function Declaration */
Std_ReturnType TMR0_Inti(const timer0_t *_timer);
Std_ReturnType TMR0_DeInti(const timer0_t *_timer);
Std_ReturnType TMR0_Write_Value(const timer0_t *_timer, u8 _value);
Std_ReturnType TMR0_Read_Value(const timer0_t *_timer, u8 *_value);

#endif	/* HAL_TIMER0_H */

