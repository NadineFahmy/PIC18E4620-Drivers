/* 
 * File:   MCAL_INTERRUPT_manager.c
 * Author: Nadine
 *
 * Created on November 20, 2023, 7:01 PM
 */

#include "MCAL_INTERRUPT_manager.h"

static volatile u8 RB4_Flag = 1;
static volatile u8 RB5_Flag = 1;
static volatile u8 RB6_Flag = 1;
static volatile u8 RB7_Flag = 1;

#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
void __interrupt() InterruptManagerHigh(void){
    if((INTCONbits.INT0IE == INT_ENABLE) && (INT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }
    else { }
    
    if((INTCON3bits.INT2IE == INT_ENABLE) && (INT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    
    else { }
    
};

void __interrupt(low_priority) InterruptManagerLow(void){
    if((INTCON3bits.INT1E == INT_ENABLE) && (INT_OCCUR == INTCON3bits.INT1F)){
        INT1_ISR();
    }
    else { }
};

#else

void __interrupt() InterruptManager(void){
    if((INTCONbits.INT0IE == INT_ENABLE) && (INT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }
    
    else { }
    
    if((INTCON3bits.INT1E == INT_ENABLE) && (INT_OCCUR == INTCON3bits.INT1F)){
        INT1_ISR();
    }
    
    else { }
    
    if((INTCON3bits.INT2IE == INT_ENABLE) && (INT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    
    else { }
    
    if((INTCONbits.RBIE == INT_ENABLE) && (INT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB4 == HIGH)
            && (RB4_Flag = 1)){
        RB4_Flag = 0;
        RB4_ISR(0);
    }
    
    else { }
    
    if((INTCONbits.RBIE == INT_ENABLE) && (INT_OCCUR == INTCONbits.RBIF && (PORTBbits.RB4 == LOW)
            && (RB4_Flag = 0)){
        RB4_Flag = 1;
        RB4_ISR(1);
    }
    
     if((INTCONbits.RBIE == INT_ENABLE) && (INT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB5 == HIGH
             && (RB5_Flag = 1))){
        RB5_Flag = 0;
        RB5_ISR(0);
    }
    
    else { }
    
    if((INTCONbits.RBIE == INT_ENABLE) && (INT_OCCUR == INTCONbits.RBIF && (PORTBbits.RB5 == LOW)
            && (RB5_Flag = 0)){
        RB5_Flag = 1;
        RB5_ISR(1);
    }
    
    else { }
    
         if((INTCONbits.RBIE == INT_ENABLE) && (INT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB6 == HIGH
             && (RB6_Flag = 1))){
        RB6_Flag = 0;
        RB6_ISR(0);
    }
    
    else { }
    
    if((INTCONbits.RBIE == INT_ENABLE) && (INT_OCCUR == INTCONbits.RBIF && (PORTBbits.RB6 == LOW)
            && (RB6_Flag = 0)){
        RB6_Flag = 1;
        RB6_ISR(1);
    }
    
    else { }
    
         if((INTCONbits.RBIE == INT_ENABLE) && (INT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB7 == HIGH
             && (RB7_Flag = 1))){
        RB7_Flag = 0;
        RB7_ISR(0);
    }
    
    else { }
    
    if((INTCONbits.RBIE == INT_ENABLE) && (INT_OCCUR == INTCONbits.RBIF && (PORTBbits.RB7 == LOW)
            && (RB7_Flag = 0)){
        RB7_Flag = 1;
        RB7_ISR(1);
    }
    
    else { }
    
    if((PIE1bits.ADIE == INT_ENABLE) && (INT_OCCUR == PIR1bits.ADIF)){
        ADC_ISR();
    }
    
    else { }
    
    if((INTCONbits.TMR0IE == INT_ENABLE) && (INT_OCCUR == INTCONbits.TMR0IF)){
        TMR0_ISR();
    }
    
    else { }
    
    if((PIE1bits.TMR1IE == INT_ENABLE) && (INT_OCCUR == PIR1bits.TMR1IF)){
        TMR1_ISR();
    }
    
    else { }
    
    if((PIE1bits.TMR2IE == INT_ENABLE) && (INT_OCCUR == PIR1bits.TMR2IF)){
        TMR2_ISR();
    }
    
    else { }
    
    if((PIE2bits.TMR3IE == INT_ENABLE) && (INT_OCCUR == PIR2bits.TMR3IF)){
        TMR3_ISR();
    }
    
    else { }
    
    if((PIE1bits.TXIE == INT_ENABLE) && (INT_OCCUR == PIE1bits.TXIF)){
        EUSART_TX_ISR();
    }
    
    else { }
    
    if((PIE1bits.RCIE == INT_ENABLE) && (INT_OCCUR == PIE1bits.RCIF)){
        EUSART_RX_ISR();
    }
    
    else { }
    
    if((PIE1bits.SSPIE == INT_ENABLE) && (INT_OCCUR == PIR1bits.SSPIF)){
        MSSP_I2C_ISR();
    }
    
    else { }
    
    if((PIE2bits.BCLIE == INT_ENABLE) && (INT_OCCUR == PIR2bits.BCLIF)){
        MSSP_I2C_BC_ISR();
    }
    
    else { }
    
    if((PIE1bits.CCP1IE == INT_ENABLE) && (INT_OCCUR == PIR1bits.CCP1IF)){
        CCP1_ISR();
    }
    
    else { }
    
    if((PIE2bits.BCLIE == INT_ENABLE) && (INT_OCCUR == PIR2bits.BCLIF)){
        CCP2_ISR();
    }
    
    else { }
    
};

#endif
