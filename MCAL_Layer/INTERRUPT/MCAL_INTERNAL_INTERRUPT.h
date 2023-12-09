/* 
 * File:   MCAL_INTERNAL_INTERRUPT.h
 * Author: Nadine
 *
 * Created on November 20, 2023, 7:04 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/* Section : Include */
#include "MCAL_INTERRUPT_config.h"

#if ADC_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
#define ADC_InterruptEnable()    (PIE1bits.ADIE = 1)
#define ADC_InterruptDisable()   (PIE1bits.ADIE = 0)

#define ADC_INTERRUPTFlagClear() (PIR1bits.ADIF = 0)

#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
#define ADC_HighPriorityset()         (IPR1bits.ADIP = 1)
#define ADC_LowPriorityset()          (IPR1bits.ADIP = 0)
#endif
#endif


#if TMR0_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
#define TMR0_InterruptEnable()    (INTCONbits.TMR0IE = 1)
#define TMR0_InterruptDisable()   (INTCONbits.TMR0IE = 0)

#define TMR0_INTERRUPTFlagClear() (INTCONbits.TMR0IF = 0)

#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
#define TMR0_HighPriorityset()         (INTCON2bits.TMR0IP = 1)
#define TMR0_LowPriorityset()          (INTCON2bits.TMR0IP = 0)
#endif
#endif



#if TMR1_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
#define TMR1_InterruptEnable()    (PIE1bits.TMR1IE = 1)
#define TMR1_InterruptDisable()   (PIE1bits.TMR1IE = 0)

#define TMR1_INTERRUPTFlagClear() (PIR1bits.TMR1IF = 0)

#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
#define TMR1_HighPriorityset()         (IPR1bits.TMR1IP = 1)
#define TMR1_LowPriorityset()          (IPR1bits.TMR1IP = 0)
#endif
#endif



#if TMR2_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
#define TMR2_InterruptEnable()    (PIE1bits.TMR2IE = 1)
#define TMR2_InterruptDisable()   (PIE1bits.TMR2IE = 0)

#define TMR2_INTERRUPTFlagClear() (PIR1bits.TMR2IF = 0)

#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
#define TMR2_HighPriorityset()         (IPR1bits.TMR2IP = 1)
#define TMR2_LowPriorityset()          (IPR1bits.TMR2IP = 0)
#endif
#endif



#if TMR3_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
#define TMR3_InterruptEnable()    (PIE2bits.TMR3IE = 1)
#define TMR3_InterruptDisable()   (PIE2bits.TMR3IE = 0)

#define TMR3_INTERRUPTFlagClear() (PIR2bits.TMR3IF = 0)

#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
#define TMR3_HighPriorityset()         (IPR2bits.TMR3IP = 1)
#define TMR3_LowPriorityset()          (IPR2bits.TMR3IP = 0)
#endif
#endif



#if EUSART_TX_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
#define EUSART_TX_InterruptEnable()    (PIE1bits.TXIE = 1)
#define EUSART_TX_InterruptDisable()   (PIE1bits.TXIE = 0)

#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
#define EUSART_TX_HighPriorityset()         (IPR1bits.TXIP = 1)
#define EUSART_TX_LowPriorityset()          (IPR1bits.TXIP = 0)
#endif
#endif



#if EUSART_RX_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
#define EUSART_RX_InterruptEnable()    (PIE1bits.RCIE = 1)
#define EUSART_RX_InterruptDisable()   (PIE1bits.RCIE = 0)

#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
#define EUSART_RX_HighPriorityset()         (IPR1bits.RCIP = 1)
#define EUSART_RX_LowPriorityset()          (IPR1bits.RCIP = 0)
#endif
#endif



#if MSSP_I2C_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
#define MSSP_I2C_InterruptEnable()    (PIE1bits.SSPIE = 1)
#define MSSP_I2C_BUS_COL_InterruptEnable()    (PIE2bits.BCLIE = 1)

#define MSSP_I2C_InterruptDisable()   (PIE1bits.SSPIE = 0)
#define MSSP_I2C_BUS_COL_InterruptDisable()    (PIE2bits.BCLIE = 0)

#define MSSP_I2C_INTERRUPTFlagClear() (PIR1bits.SSPIF = 0)
#define MSSP_I2C_BUS_COL_INTERRUPTFlagClear() (PIR2bits.BCLIF = 0)

#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
#define MSSP_I2C_HighPriorityset()         (IPR1bits.SSPIP = 1)
#define MSSP_I2C_BUS_COL_HighPriorityset()      (IPR2bits.BCLIP = 1)

#define MSSP_I2C_LowPriorityset()                  (IPR1bits.SSPIP = 0)
#define MSSP_I2C_BUS_COL_LowPriorityset()          (IPR2bits.BCLIP = 0)
#endif
#endif


#if CCP1_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
#define CCP1_InterruptEnable()    (PIE1bits.CCP1IE = 1)
#define CCP1_InterruptDisable()   (PIE1bits.CCP1IE = 0)

#define CCP1_INTERRUPTFlagClear() (PIR1bits.CCP1IF = 0)

#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
#define CCP1_HighPriorityset()         (IPR1bits.CCP1IP = 1)
#define CCP1_LowPriorityset()          (IPR1bits.CCP1IP = 0)
#endif
#endif

#if CCP2_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
#define CCP2_InterruptEnable()    (PIE2bits.BCLIE = 1)
#define CCP2_InterruptDisable()   (PIE2bits.BCLIE = 0)

#define CCP2_INTERRUPTFlagClear() (PIR2bits.BCLIF = 0)

#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
#define CCP2_HighPriorityset()         (IPR2bits.BCLIP = 1)
#define CCP2_LowPriorityset()          (IPR2bits.BCLIP = 0)
#endif
#endif

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

