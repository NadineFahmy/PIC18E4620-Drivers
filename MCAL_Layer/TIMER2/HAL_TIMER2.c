/* 
 * File:   HAL_TIMER2.c
 * Author: Nadine
 *
 * Created on November 25, 2023, 6:31 PM
 */

#include "HAL_TIMER2.h"

#if TMR2_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
static void  (*TMR2_InterruptHandler)(void) = NULL;
#endif

static u8 timer2_preload = 0;

Std_ReturnType TMR2_Inti(const timer2_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    
    else { 
        TIMER2_MODULE_DISABLE();
        
        TIMER2_PRESCALER_SELECT(_timer->timer2_prescaler_value);
        TIMER2_POSTSCALER_SELECT(_timer->timer2_postscaler_value);
        
        TMR2 = _timer->timer2_preload_value;
        timer2_preload = _timer->timer2_preload_value;
        
#if TMR2_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
        TMR2_InterruptEnable();
        TMR2_INTERRUPTFlagClear();
        TMR2_InterruptHandler = _timer->TMR2_InterruptHandler;
#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
        INT_PRIORITYLevelsEnable();

        if(INT_HIGH_PRIORITY ==_timer->priority){
            INT_GlobalInterruptHighEnable();
            TMR2_HighPriorityset();
        }
        else if(INT_LOW_PRIORITY ==_timer->priority){
            INT_GlobalInterruptLowEnable();
            TMR2_LowPriorityset();
        }
        else {}
#else
        INT_GlobalInterruptEnable();
        INT_PeripheralInterruptEnable();
#endif
#endif
        
        TIMER2_MODULE_ENABLE();
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType TMR2_DeInti(const timer2_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    
    else { 
        
         TIMER2_MODULE_DISABLE();
        
#if TMR2_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
        TMR2_InterruptDisable();
#endif
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType TMR2_Write_Value(const timer2_t *_timer, u8 _value){
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    
    else { 
        TMR2 = _value;
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType TMR2_Read_Value(const timer2_t *_timer, u8 *_value){
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer || NULL == _value){
        ret = E_NOT_OK;
    }
    
    else { 
        
        *_value = TMR2;
        ret = E_OK;
    }
    return ret;
}

void TMR2_ISR(void){
    TMR2_INTERRUPTFlagClear();
    TMR2 = timer2_preload;
    if(TMR2_InterruptHandler){
        TMR2_InterruptHandler();
    }
};