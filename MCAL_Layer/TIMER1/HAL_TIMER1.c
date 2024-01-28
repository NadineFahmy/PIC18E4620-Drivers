/* 
 * File:   HAL_TIMER1.c
 * Author: Nadine
 *
 * Created on November 25, 2023, 1:31 PM
 */

#include "HAL_TIMER1.h"

#if TMR1_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
static void  (*TMR1_InterruptHandler)(void) = NULL;
#endif

static u16 timer1_preload = 0;

static inline void Timer1_Mode_Select(const timer1_t *_timer);

Std_ReturnType TMR1_Inti(const timer1_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    
    else { 
        TIMER1_MODULE_DISABLE();
        TIMER1_PRESCALER_SELECT(_timer->timer1_prescaler_value);
        Timer1_Mode_Select(_timer);
        TMR1H = (_timer->timer1_preload_value) >> 8;
        TMR1L = (u8)(_timer->timer1_preload_value);
        timer1_preload = _timer->timer1_preload_value;
        
#if TMR1_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
        TMR1_InterruptEnable();
        TMR1_INTERRUPTFlagClear();
        TMR1_InterruptHandler = _timer->TMR1_InterruptHandler;
#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
        INT_PRIORITYLevelsEnable();

        if(INT_HIGH_PRIORITY ==_timer->priority){
            INT_GlobalInterruptHighEnable();
            TMR1_HighPriorityset();
        }
        else if(INT_LOW_PRIORITY ==_timer->priority){
            INT_GlobalInterruptLowEnable();
            TMR1_LowPriorityset();
        }
        else {}
#else
        INT_GlobalInterruptEnable();
        INT_PeripheralInterruptEnable();
#endif
#endif
        TIMER1_MODULE_ENABLE();
    }
    return ret;
}

Std_ReturnType TMR1_DeInti(const timer1_t *_timer){
   Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    
    else { 
        TIMER1_MODULE_DISABLE();
        
#if TMR1_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
        TMR1_InterruptDisable();
#endif
    }
    return ret; 
}

Std_ReturnType TMR1_Write_Value(const timer1_t *_timer, u16 _value){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    
    else { 
        TMR1H = (_value) >> 8;
        TMR1L = (u8)(_value);
    }
    return ret;
}

Std_ReturnType TMR1_Read_Value(const timer1_t *_timer, u16 *_value){
    Std_ReturnType ret = E_NOT_OK;
    u8 l_tmr1l = 0, l_tmr1h = 0;
    if(NULL == _timer || NULL == _value){
        ret = E_NOT_OK;
    }
    
    else { 
        l_tmr1l = TMR0L;
        l_tmr1h = TMR0H;
        *_value = (u16)((l_tmr1h << 8) + l_tmr1h) ;
    }
    return ret;
}

void TMR1_ISR(void){
    TMR1_INTERRUPTFlagClear();
    TMR1H = (timer1_preload) >> 8;
    TMR1L = (u8)(timer1_preload);
    if(TMR1_InterruptHandler){
        TMR1_InterruptHandler();
    }
}

static inline void Timer1_Mode_Select(const timer1_t *_timer){
    if(TIMER1_TIMER_MODE == _timer->timer1_mode){
        TIMER1_TIMER_MODE_ENABLE();
    }
    
    else if(TIMER1_COUNTER_MODE == _timer->timer1_mode){
        TIMER1_COUNTER_MODE_ENABLE();
        
        if(TIMER1_ASYNC_COUNTER_MODE ==_timer->timer1_counter_mode){
            TIMER1_ASYNC_COUNTER_MODE_ENABLE();
        }
        else if(TIMER1_SYNC_COUNTER_MODE ==_timer->timer1_counter_mode){
            TIMER1_SYNC_COUNTER_MODE_ENABLE();
        }
        else{}
    }
    else{}
}
