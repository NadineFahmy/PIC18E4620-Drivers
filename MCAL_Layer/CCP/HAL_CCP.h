/* 
 * File:   HAL_CCP.h
 * Author: Nadine
 *
 * Created on December 3, 2023, 1:04 PM
 */

#ifndef HAL_CCP_H
#define	HAL_CCP_H

#include "HAL_CPP_config.h"
#include <xc.h>
#include "../MCAL_STD_TYPES.h"
#include "../../MCAL_Layer/GPIO/HAL_GPIO.h"
#include "../../MCAL_Layer/INTERRUPT/MCAL_INTERNAL_INTERRUPT.h"

#define CCP_MODULE_DISABLE                 ((u8)0x00)
#define CCP_CAPTURE_MODE_1_FALLING_EDGE    ((u8)0x04)
#define CCP_CAPTURE_MODE_1_RISING_EDGE     ((u8)0x05)
#define CCP_CAPTURE_MODE_4_RISING_EDGE     ((u8)0x06)
#define CCP_CAPTURE_MODE_16_RISING_EDGE    ((u8)0x07)
#define CCP_COMPARE_MODE_SET_PIN_LOW       ((u8)0x08)
#define CCP_COMPARE_MODE_SET_PIN_HIGH      ((u8)0x09)
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH   ((u8)0x02)
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT  ((u8)0x0A)
#define CCP_COMPARE_MODE_GEN_EVENT         ((u8)0x0B)
#define CCP_PWM_MODE                       ((u8)0x0C)

#define CCP1_CAPTURE_NOT_READY              0X00
#define CCP1_CAPTURE_READY                  0X01

#define CCP1_COMPARE_NOT_READY              0X00
#define CCP1_COMPARE_READY                  0X01

#define CCP_TIMER2_POSTSCALER_DIV_BY_1       1
#define CCP_TIMER2_POSTSCALER_DIV_BY_2       2
#define CCP_TIMER2_POSTSCALER_DIV_BY_3       3
#define CCP_TIMER2_POSTSCALER_DIV_BY_4       4
#define CCP_TIMER2_POSTSCALER_DIV_BY_5       5
#define CCP_TIMER2_POSTSCALER_DIV_BY_6       6
#define CCP_TIMER2_POSTSCALER_DIV_BY_7       7
#define CCP_TIMER2_POSTSCALER_DIV_BY_8       8
#define CCP_TIMER2_POSTSCALER_DIV_BY_9       9
#define CCP_TIMER2_POSTSCALER_DIV_BY_10      10
#define CCP_TIMER2_POSTSCALER_DIV_BY_11      11
#define CCP_TIMER2_POSTSCALER_DIV_BY_12      12
#define CCP_TIMER2_POSTSCALER_DIV_BY_13      13
#define CCP_TIMER2_POSTSCALER_DIV_BY_14      14
#define CCP_TIMER2_POSTSCALER_DIV_BY_15      15
#define CCP_TIMER2_POSTSCALER_DIV_BY_16      16

#define CCP_TIMER2_PRESCALER_DIV_BY_1        1
#define CCP_TIMER2_PRESCALER_DIV_BY_4        4
#define CCP_TIMER2_PRESCALER_DIV_BY_16       16

#define CCP1_SET_MODE(_CONFIG)  (CCP1CONbits.CCP1M = _CONFIG)
#define CCP2_SET_MODE(_CONFIG)  (CCP2CONbits.CCP2M = _CONFIG)

typedef enum{
    CCP_CAPTURE_MODE_SELECTED = 0, /* Select CCP Capture Mode */
    CCP_COMPARE_MODE_SELECTED,     /* Select CCP Compare Mode */
    CCP_PWM_MODE_SELECTED          /* Select CCP PWM Mode */
}ccp1_mode_t;

typedef union{
    struct{
        u8 ccpr_low;  /* CCPR1 low register */
        u8 ccpr_high; /* CCPR1 high register */
    };
    struct{
        u16 ccpr_16Bit; /* Read CCPR1 as a 16 Bit value */
    };
}CCP_REG_T;

typedef enum{
    CCP1_INST = 0,
    CCP2_INST
}ccp_inst_t;

typedef enum{
    CCP1_CCP2_TIMER3 = 0,
    CCP1_TIMER1_CCP2_TIMER3,
    CCP1_CCP2_TIMER1
}ccp_capture_timer_t;

typedef struct{
    ccp_inst_t ccp_inst;
    ccp1_mode_t ccp_mode;      /* CCP main mode */
    u8 ccp_mode_variant;    /* CCP selected mode variant */
    pin_config_t ccp_pin;      /* CCP Pin I/O configurations */
    ccp_capture_timer_t ccp_capture_timer;
#if (( CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED ) || ( CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED ))
    u32 PWM_Frequency;      /* CCP PWM mode frequency */
    u8 timer2_postscaler_value;
    u8 timer2_prescaler_value;
#endif
    
#if CCP1_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
    void (* CCP1_InterruptHandler)(void);   /* Call back used for all CCP1 Modes */
    INT_priority_cfg CCP1_priority;        /* Configure the CCP1 mode interrupt */
#endif
    
#if CCP2_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
    void (* CCP2_InterruptHandler)(void);   /* Call back used for all CCP2 Modes */
    INT_priority_cfg CCP2_priority;   /* Configure the CCP1 mode interrupt */
#endif
}ccp_t;

Std_ReturnType CCP_Init(const ccp_t *_ccp_obj);
Std_ReturnType CCP_DeInit(const ccp_t *_ccp_obj);

#if CCP1_CFG_SELECTED_MODE==CCP_CFG_CAPTURE_MODE_SELECTED
Std_ReturnType CCP1_IsCapturedDataReady(u8 *_capture_status);
Std_ReturnType CCP1_Capture_Mode_Read_Value(u16 *capture_value);
#endif

#if CCP1_CFG_SELECTED_MODE==CCP_CFG_COMPARE_MODE_SELECTED
Std_ReturnType CCP_IsCompareComplete(u8 *_compare_status);
Std_ReturnType CCP_Compare_Mode_Set_Value(const ccp_t *_ccp_obj, u16 compare_value);
#endif

#if ((CCP1_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED) || (CCP2_CFG_SELECTED_MODE==CCP_CFG_PWM_MODE_SELECTED))
Std_ReturnType CCP_PWM_Set_Duty(const ccp_t *_ccp_obj, const u8 _duty);
Std_ReturnType CCP_PWM_Start(const ccp_t *_ccp_obj);
Std_ReturnType CCP_PWM_Stop(const ccp_t *_ccp_obj);
#endif


#endif	/* HAL_CCP_H */

