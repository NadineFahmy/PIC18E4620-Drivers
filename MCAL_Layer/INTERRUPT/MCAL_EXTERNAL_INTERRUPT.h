/* 
 * File:   MCAL_EXTERNAL_INTERRUPT.h
 * Author: Nadine
 *
 * Created on November 20, 2023, 7:06 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* Section : Include */
#include "MCAL_INTERRUPT_config.h"

/*Section : Macro Function Declaration */
#if EXTERNAL_INT_INTX_Enable==INT_FEATURE_ENABLE

#define EXT_INT0_INTERRUPTEnable()         (INTCONbits.INT0IE = 1)
#define EXT_INT0_INTERRUPTDisable()        (INTCONbits.INT0IE = 0)

#define EXT_INT0_INTERRUPTFlagClear()      (INTCONbits.INT0IF = 0)

#define EXT_INT0_RisingEdgeset()           (INTCON2bits.INTEDG0 = 1)
#define EXT_INT0_FallingEdgeset()          (INTCON2bits.INTEDG0 = 0)

#define EXT_INT1_INTERRUPTEnable()         (INTCON3bits.INT1IE = 1)
#define EXT_INT1_INTERRUPTDisable()        (INTCON3bits.INT1IE = 0)

#define EXT_INT1_INTERRUPTFlagClear()      (INTCON3bits.INT1IF = 0)

#define EXT_INT1_RisingEdgeset()           (INTCON2bits.INTEDG1 = 1)
#define EXT_INT1_FallingEdgeset()          (INTCON2bits.INTEDG1 = 0)

#define EXT_INT2_INTERRUPTEnable()         (INTCON3bits.INT2IE = 1)
#define EXT_INT2_INTERRUPTDisable()        (INTCON3bits.INT2IE = 0)

#define EXT_INT2_INTERRUPTFlagClear()      (INTCON3bits.INT2IF = 0)

#define EXT_INT2_RisingEdgeset()           (INTCON2bits.INTEDG2 = 1)
#define EXT_INT2_FallingEdgeset()          (INTCON2bits.INTEDG2 = 0)

#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
#define EXT_INT1_HighPriorityset()         (INTCON3bits.INT1IP = 1)
#define EXT_INT1_LowPriorityset()          (INTCON3bits.INT1IP = 0)

#define EXT_INT2_HighPriorityset()         (INTCON3bits.INT2IP = 1)
#define EXT_INT2_LowPriorityset()          (INTCON3bits.INT2IP = 0)
#endif

#endif

#if EXTERNAL_INT_OnChange_Enable==INT_FEATURE_ENABLE
#define EXT_RBx_INTERRUPTEnable()         (INTCONbits.RBIE = 1)
#define EXT_RBx_INTERRUPTDisable()        (INTCONbits.RBIE = 0)

#define EXT_RBx_INTERRUPTFlagClear()      (INTCONbits.RBIF = 0)

#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
#define EXT_RBx_HighPriorityset()         (INTCON2bits.RBIP = 1)
#define EXT_RBx_LowPriorityset()          (INTCON2bits.RBIP = 0)
#endif
#endif

/*Section : Datatype Declaration */
typedef enum{
    INT_FALLING_EDGE,
    INT_RISING_EDGE        
}INT_INTx_edge;

typedef enum{
    INT_EXT_INT0,
    INT_EXT_INT1,
    INT_EXT_INT2
}INT_INTx_src;

typedef struct{
    void(* EXT_InterruptHandler)(void);
    pin_config_t mcu_pin;
    INT_INTx_edge edge;
    INT_INTx_src source;
    INT_priority_cfg priority;
}INT_INTx_t;

typedef struct{
    void(* EXT_InterruptHandler_HIGH)(void);
    void(* EXT_InterruptHandler_LOW)(void);
    pin_config_t mcu_pin;
    INT_priority_cfg priority;
}INT_RBx_t;

/*Section : Function Declaration */
Std_ReturnType INT_INTx_Inti(const INT_INTx_t *int_obj);
Std_ReturnType INT_INTx_DeInti(const INT_INTx_t *int_obj);

Std_ReturnType INT_RBx_Inti(const INT_RBx_t *int_obj);
Std_ReturnType INT_RBx_DeInti(const INT_RBx_t *int_obj);
        
#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

