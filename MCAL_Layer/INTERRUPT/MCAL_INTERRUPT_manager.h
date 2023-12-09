/* 
 * File:   MCAL_INTERRUPT_manager.h
 * Author: Nadine
 *
 * Created on November 20, 2023, 7:08 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

#include "MCAL_INTERRUPT_config.h"

void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

void RB4_ISR(u8 RB4_Source);
void RB5_ISR(u8 RB5_Source);
void RB6_ISR(u8 RB6_Source);
void RB7_ISR(u8 RB7_Source);

void ADC_ISR(void);

void TMR0_ISR(void);
void TMR1_ISR(void);
void TMR2_ISR(void);
void TMR3_ISR(void);

void EUSART_TX_ISR(void);
void EUSART_RX_ISR(void);

void MSSP_I2C_ISR(void);
void MSSP_I2C_BC_ISR(void);

void CCP1_ISR(void);
void CCP2_ISR(void);

#endif	/* MCAL_INTERRUPT_MANAGER_H */

