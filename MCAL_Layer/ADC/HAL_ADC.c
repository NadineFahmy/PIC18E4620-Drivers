/* 
 * File:   HAL_ADC.c
 * Author: Nadine
 *
 * Created on November 22, 2023, 4:06 PM
 */

#include "HAL_ADC.h"

#if ADC_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
static void  (*ADC_InterruptHandler)(void) = NULL;
#endif

static inline void ADC_input_channel_port_config(ADC_channel_select_t channel);
static inline void select_result_format(const ADC_config_t *_adc);
static inline void config_voltage_referance(const ADC_config_t *_adc);
void ADC_ISR(void);

Std_ReturnType ADC_Inti(const ADC_config_t *_adc){
    
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    
    else { 
        ADC_CONVERSION_DISABLE();
        ADCON2bits.ACQT = _adc->acquisition_time;
        ADCON2bits.ADCS = _adc->conversion_clock;
        
        ADCON0bits.CHS = _adc->ADC_channel;
        ADC_input_channel_port_config(_adc->ADC_channel);
        
        #if ADC_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
        INT_GlobalInterruptEnable();
        INT_PeripheralInterruptEnable();
        ADC_InterruptEnable();
        ADC_INTERRUPTFlagClear();
        
        #if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
        if(INT_HIGH_PRIORITY == _adc->priority){ ADC_HighPriorityset(); }
        else if(INT_LOW_PRIORITY == _adc->priority){ ADC_LowPriorityset(); }
        else {}
        #endif
        ADC_InterruptHandler = *_adc->ADC_InterruptHandler;
        #endif
        
        select_result_format(_adc);
        config_voltage_referance(_adc);
        ADC_CONVERSION_ENABLE();
        
        ret = E_OK;
    }
    return ret;
};

Std_ReturnType ADC_DeInti(const ADC_config_t *_adc){
    
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    
    else { 
        ADC_CONVERSION_DISABLE();
        
        #if ADC_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
        ADC_InterruptDisable();
        #endif
        
        ret = E_OK;
    }
    return ret;
};

Std_ReturnType ADC_SelectChannel(const ADC_config_t *_adc, ADC_channel_select_t channel){
    
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    
    else { 
        ADCON0bits.CHS = channel;
        ADC_input_channel_port_config(channel);
        
        ret = E_OK;
    }
    return ret;
};

Std_ReturnType ADC_StartConversion(const ADC_config_t *_adc){
    
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    
    else { 
        ADC_START_CONVERSION();
        ret = E_OK;
    }
    return ret;
};

Std_ReturnType ADC_IsConversionDone(const ADC_config_t *_adc, u8 *conversion_status){
    
    Std_ReturnType ret = E_NOT_OK;
    
    if((NULL == _adc) || (NULL == conversion_status)){
        ret = E_NOT_OK;
    }
    
    else { 
        //*conversion_status = (u8)(!(ADC_CONVERSION_STATUS()));
        *conversion_status = (u8)(!(ADCON0bits.GO_nDONE));
        ret = E_OK;
    }
    return ret;
};

Std_ReturnType ADC_GetConversionResult(const ADC_config_t *_adc, adc_result_t *conversion_result){
    
    Std_ReturnType ret = E_NOT_OK;
    
    if((NULL == _adc) || NULL == (conversion_result)){
        ret = E_NOT_OK;
    }
    
    else { 
        if(ADC_RESULT_RIGHT == _adc->result_format){
            *conversion_result = (adc_result_t)((ADRESH << 8) + ADRESL);
        }
        
        else if(ADC_RESULT_LEFT == _adc->result_format){
            *conversion_result = (adc_result_t)(((ADRESH << 8) + ADRESL) >> 6 );
        }
        
        else { 
            *conversion_result = (adc_result_t)((ADRESH << 8) + ADRESL);
        }
        
        ret = E_OK; 
    }
    return ret;
};

Std_ReturnType ADC_GetConversion_Blocking(const ADC_config_t *_adc, ADC_channel_select_t channel, adc_result_t *conversion_result){
    
    Std_ReturnType ret = E_NOT_OK;
    u8 l_conversion_result = 0;
    
    if((NULL == _adc) || (NULL == conversion_result)){
        ret = E_NOT_OK;
    }
    
    else { 
        ret = ADC_SelectChannel(_adc, channel);
        ret = ADC_StartConversion(_adc);
        
        while(ADCON0bits.GO_nDONE);
        ret = ADC_GetConversionResult(_adc, conversion_result);
    }
    return ret;
};

Std_ReturnType ADC_StartConversion_Interrupt(const ADC_config_t *_adc, ADC_channel_select_t channel){
    
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    
    else { 
        ret = ADC_SelectChannel(_adc, channel);
        ret = ADC_StartConversion(_adc);
    }
    return ret;
};

static inline void ADC_input_channel_port_config(ADC_channel_select_t channel){
    switch(channel){
        case ADC_CHANNEL_AN0 : SET_BIT(TRISA, _TRISA_RA0_POSN); break;
        case ADC_CHANNEL_AN1 : SET_BIT(TRISA, _TRISA_RA1_POSN); break;
        case ADC_CHANNEL_AN2 : SET_BIT(TRISA, _TRISA_RA2_POSN); break;
        case ADC_CHANNEL_AN3 : SET_BIT(TRISA, _TRISA_RA3_POSN); break;
        case ADC_CHANNEL_AN4 : SET_BIT(TRISA, _TRISA_RA5_POSN); break;
        case ADC_CHANNEL_AN5 : SET_BIT(TRISE, _TRISA_RA0_POSN); break;
        case ADC_CHANNEL_AN6 : SET_BIT(TRISE, _TRISA_RA1_POSN); break;
        case ADC_CHANNEL_AN7 : SET_BIT(TRISE, _TRISA_RA2_POSN); break;
        case ADC_CHANNEL_AN8 : SET_BIT(TRISB, _TRISA_RA2_POSN); break;
        case ADC_CHANNEL_AN9 : SET_BIT(TRISB, _TRISA_RA3_POSN); break;
        case ADC_CHANNEL_AN10 : SET_BIT(TRISB, _TRISA_RA1_POSN); break;
        case ADC_CHANNEL_AN11 : SET_BIT(TRISB, _TRISA_RA4_POSN); break;
        case ADC_CHANNEL_AN12: SET_BIT(TRISB, _TRISA_RA0_POSN); break;
    }
};

static inline void select_result_format(const ADC_config_t *_adc){
    if(ADC_RESULT_RIGHT == _adc->result_format){
        ADC_RESULT_RIGHT_FORMAT();
    }
    else if(ADC_RESULT_LEFT == _adc->result_format){
        ADC_RESULT_LEFT_FORMAT();
    }
    else { 
        ADC_RESULT_RIGHT_FORMAT();
    }
};

static inline void config_voltage_referance(const ADC_config_t *_adc){
    if(ADC_VOLTAGE_REFERANCE_ENABLE == _adc->voltage_referance){
        ADC_ENABLE_VOLTAGE_REFERANCE();
    }
    else if(ADC_VOLTAGE_REFERANCE_DISABLE == _adc->voltage_referance){
        ADC_DISABLE_VOLTAGE_REFERANCE();
    }
    else { 
        ADC_DISABLE_VOLTAGE_REFERANCE();
    }
};

void ADC_ISR(void){
    ADC_INTERRUPTFlagClear();
    if(ADC_InterruptHandler){
        ADC_InterruptHandler();
    }
};