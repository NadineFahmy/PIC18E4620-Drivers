/* 
 * File:   HAL_ADC.h
 * Author: Nadine
 *
 * Created on November 22, 2023, 4:06 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/* Section : Include */
#include <xc.h>
//#include <pic18f4620.h>
#include "../MCAL_STD_TYPES.h"
#include "../GPIO/HAL_GPIO.h"
#include "../INTERRUPT/MCAL_INTERNAL_INTERRUPT.h"
#include "HAL_ADC_config.h"

/*Section : Macro Declaration */
#define ADC_AN0_ANALOG_FUNCTIONALTY   0x0E
#define ADC_AN1_ANALOG_FUNCTIONALTY   0x0D
#define ADC_AN2_ANALOG_FUNCTIONALTY   0x0C
#define ADC_AN3_ANALOG_FUNCTIONALTY   0x0B
#define ADC_AN4_ANALOG_FUNCTIONALTY   0x0A
#define ADC_AN5_ANALOG_FUNCTIONALTY   0x09
#define ADC_AN6_ANALOG_FUNCTIONALTY   0x08
#define ADC_AN7_ANALOG_FUNCTIONALTY   0x07
#define ADC_AN8_ANALOG_FUNCTIONALTY   0x06
#define ADC_AN9_ANALOG_FUNCTIONALTY   0x05
#define ADC_AN10_ANALOG_FUNCTIONALTY  0x04
#define ADC_AN11_ANALOG_FUNCTIONALTY  0x03
#define ADC_AN12_ANALOG_FUNCTIONALTY  0x02
#define ADC_ALL_ANALOG_FUNCTIONALTY   0x00
#define ADC_ALL_DIGITAL_FUNCTIONALTY  0x0F

#define ADC_RESULT_RIGHT 0x01U
#define ADC_RESULT_LEFT  0x00U

#define ADC_VOLTAGE_REFERANCE_ENABLE  0x01U
#define ADC_VOLTAGE_REFERANCE_DISABLE 0x00U

#define ADC_CONVERSION_COMPLETED  1
#define ADC_CONVERSION_INPROGRESS 0

/*Section : Macro Function Declaration */
#define ADC_CONVERSION_STATUS() (ADCON0bits.GO_nDONE)

#define ADC_START_CONVERSION() (ADCON0bits.GODONE = 1)

#define ADC_CONVERSION_ENABLE() (ADCON0bits.ADON = 1)
#define ADC_CONVERSION_DISABLE() (ADCON0bits.ADON = 0)

#define ADC_ENABLE_VOLTAGE_REFERANCE() do{ADCON1bits.VCFG0 = 1;\
                                          ADCON1bits.VCFG1 = 1;}while(0)
#define ADC_DISABLE_VOLTAGE_REFERANCE() do{ADCON1bits.VCFG0 = 0;\
                                          ADCON1bits.VCFG1 = 0;}while(0)

#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_CONFIG) (ADCON1bits.PCFG = _CONFIG)

#define ADC_RESULT_RIGHT_FORMAT() (ADCON2bits.ADFM = 1)
#define ADC_RESULT_LEFT_FORMAT() (ADCON2bits.ADFM = 0)

/*Section : Datatype Declaration */
typedef enum {
    ADC_CHANNEL_AN0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12
}ADC_channel_select_t;

typedef enum {
    ADC_0_TAD,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD
}ADC_acquisition_time_t;

typedef enum {
    ADC_CONVERSION_CLOCK_FOSC_DIV_2,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64
}ADC_conversion_clock_t;

typedef struct{
#if ADC_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
    void(* ADC_InterruptHandler)(void);
    INT_priority_cfg priority;
#endif
//#endif
    ADC_acquisition_time_t acquisition_time;
    ADC_conversion_clock_t conversion_clock;
    ADC_channel_select_t ADC_channel;
    u8 voltage_referance: 1 ;
    u8 result_format: 1 ;
    u8 ADC_Reserved : 6 ;
}ADC_config_t;

typedef u16 adc_result_t;

/*Section : Function Declaration */
Std_ReturnType ADC_Inti(const ADC_config_t *_adc);
Std_ReturnType ADC_DeInti(const ADC_config_t *_adc);
Std_ReturnType ADC_SelectChannel(const ADC_config_t *_adc, ADC_channel_select_t channel);
Std_ReturnType ADC_StartConversion(const ADC_config_t *_adc);
Std_ReturnType ADC_IsConversionDone(const ADC_config_t *_adc, u8 *conversion_status);
Std_ReturnType ADC_GetConversionResult(const ADC_config_t *_adc, adc_result_t *conversion_result);
Std_ReturnType ADC_GetConversion_Blocking(const ADC_config_t *_adc, ADC_channel_select_t channel,
                                                                    adc_result_t *conversion_result);
Std_ReturnType ADC_StartConversion_Interrupt(const ADC_config_t *_adc, ADC_channel_select_t channel);
#endif	/* HAL_ADC_H */

