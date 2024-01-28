/* 
 * File:   MCAL_EXTERNAL_INTERRUPT.c
 * Author: Nadine
 *
 * Created on November 20, 2023, 7:06 PM
 */

#include "MCAL_EXTERNAL_INTERRUPT.h"

static void (* INT0_InterruptHandler)(void) = NULL;
static void (* INT1_InterruptHandler)(void) = NULL;
static void (* INT2_InterruptHandler)(void) = NULL;

static void (* RB4_InterruptHandler_HIGH)(void) = NULL;
static void (* RB4_InterruptHandler_LOW)(void) = NULL;
static void (* RB5_InterruptHandler_HIGH)(void) = NULL;
static void (* RB5_InterruptHandler_LOW)(void) = NULL;
static void (* RB6_InterruptHandler_HIGH)(void) = NULL;
static void (* RB6_InterruptHandler_LOW)(void) = NULL;
static void (* RB7_InterruptHandler_HIGH)(void) = NULL;
static void (* RB7_InterruptHandler_LOW)(void) = NULL;

static Std_ReturnType INT_INTx_Enable(const INT_INTx_t *int_obj);
static Std_ReturnType INT_INTx_Disable(const INT_INTx_t *int_obj);
static Std_ReturnType INT_INTx_Priority_Inti(const INT_INTx_t *int_obj);
static Std_ReturnType INT_INTx_Edge_Inti(const INT_INTx_t *int_obj);
static Std_ReturnType INT_INTx_Pin_Inti(const INT_INTx_t *int_obj);
static Std_ReturnType INT_INTx_Clear_Flag(const INT_INTx_t *int_obj);

static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void));
static Std_ReturnType INT_INTx_SetInterruptHandler(const INT_INTx_t *int_obj);

static Std_ReturnType INT_RBx_Enable(const INT_RBx_t *int_obj);
static Std_ReturnType INT_RBx_Disable(const INT_RBx_t *int_obj);
static Std_ReturnType INT_RBx_Priority_Inti(const INT_RBx_t *int_obj);
static Std_ReturnType INT_RBx_Pin_Inti(const INT_RBx_t *int_obj);


Std_ReturnType INT_INTx_Inti(const INT_INTx_t *int_obj){
    
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    
    else {
        /* Disable the External Interrupt */
            ret = INT_INTx_Disable(int_obj);
        /* Clear Interrupt Flag : External Interrupt did not occur */
            ret = INT_INTx_Clear_Flag(int_obj);
        /* Configure External Interrupt Edge */
            ret = INT_INTx_Edge_Inti(int_obj);
        /* Configure External Interrupt Priority */
            ret = INT_INTx_Priority_Inti(int_obj);
        /* Configure External Interrupt I/O pin */
            ret = INT_INTx_Pin_Inti(int_obj);
        /* Configure Default Interrupt CallBack */
            ret = INT_INTx_SetInterruptHandler(int_obj);
        /* Enable the External Interrupt */
           ret = INT_INTx_Enable(int_obj);
    }
    
    return ret;
}

void INT0_ISR(void){
    EXT_INT0_INTERRUPTFlagClear();
    
    if(INT0_InterruptHandler){ INT0_InterruptHandler(); }
    else {}
}

void INT1_ISR(void){
    EXT_INT1_INTERRUPTFlagClear();
    
    if(INT1_InterruptHandler){ INT1_InterruptHandler(); }
    else {}
}

void INT2_ISR(void){
    EXT_INT2_INTERRUPTFlagClear();
    
    if(INT2_InterruptHandler){ INT2_InterruptHandler(); }
    else {}
}

void RB4_ISR(u8 RB4_Source){
  EXT_RBx_INTERRUPTFlagClear();  
  
  if( 0 == RB4_Source) {
      if(RB4_InterruptHandler_HIGH){ RB4_InterruptHandler_HIGH(); }
      else {}
  }
  else if( 1 == RB4_Source) {
      if(RB4_InterruptHandler_LOW){ RB4_InterruptHandler_LOW(); }
      else {}
  }
  else {}
}

void RB5_ISR(u8 RB5_Source){
  EXT_RBx_INTERRUPTFlagClear();  
  
  if( 0 == RB5_Source) {
      if(RB5_InterruptHandler_HIGH){ RB5_InterruptHandler_HIGH(); }
      else {}
  }
  else if( 1 == RB5_Source) {
      if(RB5_InterruptHandler_LOW){ RB5_InterruptHandler_LOW(); }
      else {}
  }
  else {}
}

void RB6_ISR(u8 RB6_Source){
   EXT_RBx_INTERRUPTFlagClear();  
   
   if( 0 == RB6_Source) {
      if(RB6_InterruptHandler_HIGH){ RB6_InterruptHandler_HIGH(); }
      else {}
  }
  else if( 1 == RB6_Source) {
      if(RB6_InterruptHandler_LOW){ RB6_InterruptHandler_LOW(); }
      else {}
  }
  else {}
}

void RB7_ISR(u8 RB7_Source){
    EXT_RBx_INTERRUPTFlagClear(); 
    
    if( 0 == RB7_Source) {
      if(RB7_InterruptHandler_HIGH){ RB7_InterruptHandler_HIGH(); }
      else {}
  }
  else if( 1 == RB7_Source) {
      if(RB7_InterruptHandler_LOW){ RB7_InterruptHandler_LOW(); }
      else {}
  }
  else {}
}

Std_ReturnType INT_INTx_DeInti(const INT_INTx_t *int_obj){
    
        Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
       ret = E_NOT_OK;
    }
    
    else {
        ret = INT_INTx_Disable(int_obj);
    }
    
    return ret;
}

Std_ReturnType INT_RBx_Inti(const INT_RBx_t *int_obj){
    
        Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    
    else {
        
        EXT_RBx_INTERRUPTDisable();
        
        EXT_RBx_INTERRUPTFlagClear();
#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
        INT_PRIORITYLevelsEnable();
        if(int_obj->priority == INT_LOW_PRIORITY){
            INT_GlobalInterruptLowEnable();
            EXT_RBx_LowPriorityset();
        }
        else if(int_obj->priority == INT_HIGH_PRIORITY){
            INT_GlobalInterruptHighEnable(); 
            EXT_RBx_HighPriorityset();
        }
        else { /* nothing */ }
#else
        INT_GlobalInterruptEnable();
        INT_PeripheralInterruptEnable();
#endif
        ret = GPIO_pin_dir_inti(&(int_obj->mcu_pin));
        switch(int_obj->mcu_pin.pin){
            
            case PIN4_index : 
                RB4_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB4_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
            break;
            
            case PIN5_index :
                RB5_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB5_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
            break;
            
            case PIN6_index :
                RB6_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB5_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
            break;
            
            case PIN7_index :
                RB7_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB5_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
            break;
            
            default : ret = E_NOT_OK;
            
        }
        
        EXT_RBx_INTERRUPTEnable();
       
    }
    
    return ret;   
}

Std_ReturnType INT_RBx_DeInti(const INT_RBx_t *int_obj){
   
        Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    
    else {
        
    }
    
    return ret;
}

static Std_ReturnType INT_INTx_Enable(const INT_INTx_t *int_obj){
    
        Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    
    else {
        switch(int_obj->source) {
            case INT_EXT_INT0:
#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
                INT_GlobalInterruptHighEnable();
#else
                INT_GlobalInterruptEnable();
                INT_PeripheralInterruptEnable();
#endif
                EXT_INT0_INTERRUPTEnable();
                ret = E_OK;
            break;
            
            case INT_EXT_INT1:
#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
                INT_PRIORITYLevelsEnable();
                if(int_obj->priority == INT_LOW_PRIORITY){ INT_GlobalInterruptLowEnable(); }
                else if(int_obj->priority == INT_HIGH_PRIORITY){ INT_GlobalInterruptHighEnable(); }
                else { /* nothing */ }
#else
                INT_GlobalInterruptEnable();
                INT_PeripheralInterruptEnable();
#endif
                EXT_INT1_INTERRUPTEnable();
                ret = E_OK;
            break;
            
            case INT_EXT_INT2:
                INT_PRIORITYLevelsEnable();
#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
                if(int_obj->priority == INT_LOW_PRIORITY){ INT_GlobalInterruptLowEnable(); }
                else if(int_obj->priority == INT_HIGH_PRIORITY){ INT_GlobalInterruptHighEnable(); }
                else { /* nothing */ }
#else
                INT_GlobalInterruptEnable();
                INT_PeripheralInterruptEnable();
#endif
                EXT_INT2_INTERRUPTEnable();
                ret = E_OK;
            break;
            
            default : ret = E_NOT_OK;
        }
    }
    
    return ret;
}

static Std_ReturnType INT_INTx_Disable(const INT_INTx_t *int_obj){
    
        Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    
    else {
        switch(int_obj->source) {
            case INT_EXT_INT0:
                EXT_INT0_INTERRUPTDisable();
                ret = E_OK;
            break;
            
            case INT_EXT_INT1:
                EXT_INT1_INTERRUPTDisable();
                ret = E_OK;
            break;
            
            case INT_EXT_INT2:
                EXT_INT2_INTERRUPTDisable();
                ret = E_OK;
            break;
            
            default : ret = E_NOT_OK;
        };
    }
    
    return ret;
}

#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
static Std_ReturnType INT_INTx_Priority_Inti(const INT_INTx_t *int_obj){
    
        Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    
    else {
        switch(int_obj->source) {
            case INT_EXT_INT1:
                if(int_obj->priority == INT_LOW_PRIORITY){ EXT_INT1_LowPriorityset(); }
                else if(int_obj->priority == INT_HIGH_PRIORITY){ EXT_INT1_HighPriorityset(); }
                else { /* nothing */ }
                ret = E_OK;
            break;
            
            case INT_EXT_INT2:
                if(int_obj->priority == INT_LOW_PRIORITY){ EXT_INT2_LowPriorityset(); }
                else if(int_obj->priority == INT_HIGH_PRIORITY){ EXT_INT2_HighPriorityset(); }
                else { /* nothing */ }
                ret = E_OK;
            break;
            
            default : ret = E_NOT_OK;
        }
    }
    
    return ret;
}
#endif

static Std_ReturnType INT_INTx_Edge_Inti(const INT_INTx_t *int_obj){
    
        Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    
    else {
        switch(int_obj->source) {
            case INT_EXT_INT0:
                if(INT_FALLING_EDGE == int_obj->edge) { EXT_INT0_FallingEdgeset(); }
                else if(INT_RISING_EDGE == int_obj->edge) { EXT_INT0_RisingEdgeset(); }
                else { /* nothing */ }
                ret = E_OK;
            break;
            
            case INT_EXT_INT1:
                if(INT_FALLING_EDGE == int_obj->edge) { EXT_INT1_FallingEdgeset(); }
                else if(INT_RISING_EDGE == int_obj->edge) { EXT_INT1_RisingEdgeset(); }
                else { /* nothing */ }
                ret = E_OK;
            break;
            
            case INT_EXT_INT2:
                if(INT_FALLING_EDGE == int_obj->edge) { EXT_INT2_FallingEdgeset(); }
                else if(INT_RISING_EDGE == int_obj->edge) { EXT_INT2_RisingEdgeset(); }
                else { /* nothing */ }
                ret = E_OK;
            break;
            
            default : ret = E_NOT_OK;
        };
    }
    
    return ret;
}

static Std_ReturnType INT_INTx_Pin_Inti(const INT_INTx_t *int_obj){
    
        Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    
    else {
        ret = GPIO_pin_dir_inti(&(int_obj->mcu_pin));
    }
    
    return ret;
}

static Std_ReturnType INT_RBx_Enable(const INT_RBx_t *int_obj);

static Std_ReturnType INT_RBx_Disable(const INT_RBx_t *int_obj);

static Std_ReturnType INT_RBx_Priority_Inti(const INT_RBx_t *int_obj);

static Std_ReturnType INT_RBx_Pin_Inti(const INT_RBx_t *int_obj);

static Std_ReturnType INT_INTx_Clear_Flag(const INT_INTx_t *int_obj){
    
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    
    else {
        switch(int_obj->source) {
            case INT_EXT_INT0:
                EXT_INT0_INTERRUPTFlagClear();
                ret = E_OK;
            break;
            
            case INT_EXT_INT1:
                EXT_INT1_INTERRUPTFlagClear();
                ret = E_OK;
            break;
            
            case INT_EXT_INT2:
                EXT_INT2_INTERRUPTFlagClear();
                ret = E_OK;
            break;
            
            default : ret = E_NOT_OK;
        };
    }
    
    return ret;
}

static Std_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void)){
    
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == InterruptHandler){
        ret = E_NOT_OK;
    }
    
    else {
        INT0_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
    return ret;
}

static Std_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void)){
    
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == InterruptHandler){
        ret = E_NOT_OK;
    }
    
    else {
        INT1_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
    return ret;
}

static Std_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void)){
    
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == InterruptHandler){
        ret = E_NOT_OK;
    }
    
    else {
        INT2_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
    return ret;
}

static Std_ReturnType INT_INTx_SetInterruptHandler(const INT_INTx_t *int_obj){
    
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    
    else {
        switch(int_obj->source) {
            case INT_EXT_INT0:
#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
                INT_GlobalInterruptHighEnable();
                INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
#else
                INT_GlobalInterruptEnable();
                INT_PeripheralInterruptEnable();
#endif
                ret = E_OK;
            break;
            
            case INT_EXT_INT1:
#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
                if(int_obj->priority == INT_LOW_PRIORITY){ INT_GlobalInterruptLowEnable(); }
                else if(int_obj->priority == INT_HIGH_PRIORITY){ INT_GlobalInterruptHighEnable(); }
                else { /* nothing */ }
                INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);
#else
                INT_GlobalInterruptEnable();
                INT_PeripheralInterruptEnable();
#endif
                ret = E_OK;
            break;
            
            case INT_EXT_INT2:
#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
                if(int_obj->priority == INT_LOW_PRIORITY){ INT_GlobalInterruptLowEnable(); }
                else if(int_obj->priority == INT_HIGH_PRIORITY){ INT_GlobalInterruptHighEnable(); }
                else { /* nothing */ }
                INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);
#else
                INT_GlobalInterruptEnable();
                INT_PeripheralInterruptEnable();
#endif
                ret = E_OK;
            break;
            
            default : ret = E_NOT_OK;
        }
    }
    
    return ret;
}
