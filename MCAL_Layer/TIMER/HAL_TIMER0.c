/* 
 * File:   HAL_TIMER0.h
 * Author: Nadine
 *
 * Created on November 23, 2023, 7:58 PM
 */

#include "HAL_TIMER0.h"

#if TMR0_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
static void  (*TMR0_InterruptHandler)(void) = NULL;
#endif

static u16 timer0_preload = 0;

static inline void Timer0_Prescaler_Config(const timer0_t *_timer);
static inline void Timer0_Mode_Select(const timer0_t *_timer);
static inline void Timer0_Register_Size(const timer0_t *_timer);
void TMR0_ISR(void);

Std_ReturnType TMR0_Inti(const timer0_t *_timer){
    
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    
    else { 
        TIMER0_MODULE_DISABLE();
        Timer0_Prescaler_Config(_timer);
        Timer0_Mode_Select(_timer);
        Timer0_Register_Size(_timer);
        
        TMR0H = (_timer->timer0_preload_value) >> 8;
        TMR0L = (u8)(_timer->timer0_preload_value);
        
        timer0_preload = _timer->timer0_preload_value;
        
        #if TMR0_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
        TMR0_InterruptEnable();
        TMR0_INTERRUPTFlagClear();
        TMR0_InterruptHandler = _timer->TMR0_InterruptHandler;
        #if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
        INT_PRIORITYLevelsEnable();

        if(INT_HIGH_PRIORITY ==_timer->priority){
            INT_GlobalInterruptHighEnable();
            TMR0_HighPriorityset();
        }
        else if(INT_LOW_PRIORITY ==_timer->priority){
            INT_GlobalInterruptLowEnable();
            TMR0_LowPriorityset();
        }
        #else
        INT_GlobalInterruptEnable();
        INT_PeripheralInterruptEnable();
        #endif
        #endif
        TIMER0_MODULE_ENABLE();
        ret = E_OK;
    }
    return ret;
};

Std_ReturnType TMR0_DeInti(const timer0_t *_timer){
    
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    
    else { 
        TIMER0_MODULE_DISABLE();
        
        #if TMR0_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
        TMR0_InterruptDisable();
        #endif
        ret = E_OK;
    }
    return ret;
};

Std_ReturnType TMR0_Write_Value(const timer0_t *_timer, u8 _value){
    
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _timer){
        ret = E_NOT_OK;
    }
    
    else { 
        TMR0H = (_value) >> 8;
        TMR0L = (u8)(_value);
        
        ret = E_OK;
    }

    return ret;
};

Std_ReturnType TMR0_Read_Value(const timer0_t *_timer, u8 *_value){
    
    Std_ReturnType ret = E_NOT_OK;
    u8 l_tmr0l = 0, l_tmr0h = 0;
    
    if((NULL == _timer) || (NULL == _value)) {
        ret = E_NOT_OK;
    }
    
    else { 
        l_tmr0l = TMR0L;
        l_tmr0h = TMR0H;
        *_value = (u16)((l_tmr0h << 8) + l_tmr0h) ;
        ret = E_OK;
    }

    return ret;
};

void TMR0_ISR(void){
    TMR0_INTERRUPTFlagClear();
    TMR0H = (timer0_preload) >> 8;
    TMR0L = (u8)(timer0_preload);
    if(TMR0_InterruptHandler){
        TMR0_InterruptHandler();
    }
};

static inline void Timer0_Prescaler_Config(const timer0_t *_timer){
    if(TIMER0_PRESCALER_ENABLE_CFG == _timer->prescaler_enable){
        TIMER0_PRESCALER_ENABLE();
        T0CONbits.T0PS = _timer->prescaler_value;
    }
    
    else if(TIMER0_PRESCALER_DISABLE_CFG == _timer->prescaler_enable){
        TIMER0_PRESCALER_DISABLE();
    }
    
    else{}
};

static inline void Timer0_Mode_Select(const timer0_t *_timer){
    if(TIMER0_TIMER_MODE == _timer->timer0_mode){
        TIMER0_TIMER_MODE_ENABLE();
    }
    
    else if(TIMER0_COUNTER_MODE == _timer->timer0_mode){
        TIMER0_COUNTER_MODE_ENABLE();
        
        if(TIMER0_RISING_EDGE_CFG ==_timer->timer0_counter_edge ){
            TIMER0_FALLING_EDGE_ENABLE();
        }
        else if(TIMER0_RISING_EDGE_CFG ==_timer->timer0_counter_edge ){
            TIMER0_FALLING_EDGE_ENABLE();
        }
        else{}
    }
    else{}
};

static inline void Timer0_Register_Size(const timer0_t *_timer){
    if(TIMER0_8BIT_REGISTER_MODE == _timer->timer0_register_size){
        TIMER0_8BIT_REGISTER_MODE_ENABLE();
    }
    
    else if(TIMER0_16BIT_REGISTER_MODE == _timer->timer0_register_size){
        TIMER0_8BIT_REGISTER_MODE_ENABLE();
    }
    
    else{}
};