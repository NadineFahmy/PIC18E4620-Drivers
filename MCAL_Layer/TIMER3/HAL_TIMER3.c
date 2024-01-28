
/* 
 * File:   HAL_TIMER3.c
 * Author: Nadine
 *
 * Created on November 25, 2023, 6:37 PM
 */


#include "HAL_TIMER3.h"

#if TMR3_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
static void  (*TMR3_InterruptHandler)(void) = NULL;
#endif

static u16 timer3_preload = 0;

static inline void Timer3_Mode_Select(const timer3_t *_timer);

Std_ReturnType TMR3_Inti(const timer3_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    
    else { 
        TIMER3_MODULE_DISABLE();
        TIMER3_PRESCALER_SELECT(_timer->timer3_prescaler_value);
        Timer3_Mode_Select(_timer);
        TMR1H = (_timer->timer3_preload_value) >> 8;
        TMR1L = (u8)(_timer->timer3_preload_value);
        timer3_preload = _timer->timer3_preload_value;
        
#if TMR3_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
        TMR3_InterruptEnable();
        TMR3_INTERRUPTFlagClear();
        TMR3_InterruptHandler = _timer->TMR3_InterruptHandler;
#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
        INT_PRIORITYLevelsEnable();

        if(INT_HIGH_PRIORITY ==_timer->priority){
            INT_GlobalInterruptHighEnable();
            TMR3_HighPriorityset();
        }
        else if(INT_LOW_PRIORITY ==_timer->priority){
            INT_GlobalInterruptLowEnable();
            TMR3_LowPriorityset();
        }
        else {}
#else
        INT_GlobalInterruptEnable();
        INT_PeripheralInterruptEnable();
#endif
#endif
        TIMER3_MODULE_ENABLE();
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType TMR3_DeInti(const timer3_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    
    else { 
        TIMER3_MODULE_DISABLE();
        
#if TMR3_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
        TMR3_InterruptDisable();
#endif
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType TMR3_Write_Value(const timer3_t *_timer, u16 _value){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    
    else { 
        TMR3H = (_value) >> 8;
        TMR3L = (u8)(_value);
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType TMR3_Read_Value(const timer3_t *_timer, u16 *_value){
    Std_ReturnType ret = E_NOT_OK;
    u8 l_tmr3l = 0, l_tmr3h = 0;
    if(NULL == _timer || NULL == _value){
        ret = E_NOT_OK;
    }
    
    else { 
        l_tmr3l = TMR0L;
        l_tmr3h = TMR0H;
        *_value = (u16)((l_tmr3h << 8) + l_tmr3h) ;
        ret = E_OK;
    }
    return ret;
}

void TMR3_ISR(void){
    TMR3_INTERRUPTFlagClear();
    TMR1H = (timer3_preload) >> 8;
    TMR1L = (u8)(timer3_preload);
    if(TMR3_InterruptHandler){
        TMR3_InterruptHandler();
    }
}

static inline void Timer3_Mode_Select(const timer3_t *_timer){
    if(TIMER3_TIMER_MODE == _timer->timer3_mode){
        TIMER3_TIMER_MODE_ENABLE();
    }
    
    else if(TIMER3_COUNTER_MODE == _timer->timer3_mode){
        TIMER3_COUNTER_MODE_ENABLE();
        
        if(TIMER3_ASYNC_COUNTER_MODE ==_timer->timer3_counter_mode){
            TIMER3_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if(TIMER3_SYNC_COUNTER_MODE ==_timer->timer3_counter_mode){
            TIMER3_SYNC_COUNTER_MODE_ENABLE();
        }
        else{}
    }
    else{}
}
