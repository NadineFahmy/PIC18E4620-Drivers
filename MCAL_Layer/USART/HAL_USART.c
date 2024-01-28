/* 
 * File:   HAL_USART.c
 * Author: Nadine
 *
 * Created on November 26, 2023, 7:15 PM
 */

#include "HAL_USART.h"

#if EUSART_TX_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
static void  (*EUSART_TxInterruptHandler)(void) = NULL;
#endif

#if EUSART_RX_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
static void  (*EUSART_RxInterruptHandler)(void) = NULL;
static void  (*EUSART_FramingErrorHandler)(void) = NULL;
static void  (*EUSART_OverrunErrorHandler)(void) = NULL;
#endif

static void EUSART_BaudRate_Calculation(const usart_t *_eusart);
static void EUSART_ASYNC_TX_Init(const usart_t *_eusart);
static void EUSART_ASYNC_RX_Init(const usart_t *_eusart);

Std_ReturnType EUSART_ASYNC_Init(const usart_t *_eusart){
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _eusart){
        ret = E_NOT_OK;
    }
    
    else { 
        RCSTAbits.SPEN = 0;
        TRISCbits.RC7 = 1;
        TRISCbits.RC6 = 1;
        EUSART_BaudRate_Calculation(_eusart);
        EUSART_ASYNC_TX_Init(_eusart);
        EUSART_ASYNC_RX_Init(_eusart);        
        RCSTAbits.SPEN = 1;
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType EUSART_ASYNC_DeInit(const usart_t *_eusart){
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == _eusart){
        ret = E_NOT_OK;
    }
    
    else { 
        RCSTAbits.SPEN = 1;
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType EUSART_ASYNC_ReadByteBlocking(u8 *_data){
    Std_ReturnType ret = E_NOT_OK;
    while(!PIR1bits.RCIF);
#if EUSART_TX_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE    
    PIE1bits.TXIE = 1;
#endif    
    *_data = RCREG;
    return ret;
}

Std_ReturnType EUSART_ASYNC_ReadByteNonBlocking(u8 *_data){
    Std_ReturnType ret = E_NOT_OK;
    if(1 ==PIR1bits.RCIF){
        *_data = RCREG;
        ret = E_OK;
    }
    else {
        ret = E_NOT_OK;
    }

    return ret;
}

Std_ReturnType EUSART_ASYNC_Restart_RX(void){
    Std_ReturnType ret = E_OK;
    
    RCSTAbits.CREN = 0;
    RCSTAbits.CREN = 1;

    return ret;
}

Std_ReturnType EUSART_ASYNC_WriteByteBlockinge(u8 _data){
    Std_ReturnType ret = E_OK;

    while(!TXSTAbits.TRMT);
    TXREG = _data;
    
    return ret;
}

Std_ReturnType EUSART_ASYNC_WriteStringBlockinge(u8 *_data, u16 str_length){
    Std_ReturnType ret = E_OK;
    u16 char_counter = 0;
    for(char_counter = 0; char_counter < str_length; char_counter++){
        ret = EUSART_ASYNC_WriteByteBlockinge(_data[char_counter]);
    }
    return ret;
}

static void EUSART_BaudRate_Calculation(const usart_t *_eusart){
    float BaudRate_Temp = 0;
    switch(_eusart->baudrate_gen_cfg){
        case BAUDRATE_ASYNC_8BIT_LOW_SPEED:
            TXSTAbits.SYNC = 0;
            TXSTAbits.BRGH = 0;
            BAUDCONbits.BRG16 = 0;
            BaudRate_Temp = ( (_XTAL_FREQ/(float)_eusart->baudrate) /64) - 1;
        break;
        
        case BAUDRATE_ASYNC_8BIT_HIGH_SPEED:
            TXSTAbits.SYNC = 0;
            TXSTAbits.BRGH = 1;
            BAUDCONbits.BRG16 = 0;
            BaudRate_Temp = ( (_XTAL_FREQ/(float)_eusart->baudrate) /64) - 1;
        break;
        
        case BAUDRATE_ASYNC_16BIT_LOW_SPEED:
            TXSTAbits.SYNC = 0;
            TXSTAbits.BRGH = 0;
            BAUDCONbits.BRG16 = 1;
            BaudRate_Temp = ( (_XTAL_FREQ/(float)_eusart->baudrate) /64) - 1;
        break;
        
        case BAUDRATE_ASYNC_16BIT_HIGH_SPEED:
            TXSTAbits.SYNC = 0;
            TXSTAbits.BRGH = 1;
            BAUDCONbits.BRG16 = 1;
            BaudRate_Temp = ( (_XTAL_FREQ/(float)_eusart->baudrate) /64) - 1;
        break;
        
        case BAUDRATE_SYNC_8BIT:
            TXSTAbits.SYNC = 1;
            BAUDCONbits.BRG16 = 0;
            BaudRate_Temp = ( (_XTAL_FREQ/(float)_eusart->baudrate) /64) - 1;
        break;
        
        case BAUDRATE_SYNC_16BIT:
            TXSTAbits.SYNC = 1;
            BAUDCONbits.BRG16 = 1;
            BaudRate_Temp = ( (_XTAL_FREQ/(float)_eusart->baudrate) /64) - 1;
        break;
        
        default: ;
    }
    SPBRG = (u8)((u32)BaudRate_Temp);
    SPBRGH = (u8)(((u32)BaudRate_Temp) >> 8);
}

static void EUSART_ASYNC_TX_Init(const usart_t *_eusart){
    if(EUSART_ASYNC_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_enable){
        TXSTAbits.TXEN = EUSART_ASYNC_TX_ENABLE;
        EUSART_TxInterruptHandler = _eusart->EUSART_TxDefaultInterruptHandler;
if(EUSART_ASYNC_INTERRUPT_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_interrupt_enable){
        PIE1bits.TXIE = EUSART_ASYNC_INTERRUPT_TX_ENABLE;
        #if EUSART_TX_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
        EUSART_TX_InterruptEnable();
#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
        INT_PRIORITYLevelsEnable();

        if(INT_HIGH_PRIORITY ==_eusart->usart_tx_cfg.priority){
            INT_GlobalInterruptHighEnable();
            EUSART_TX_HighPriorityset();
        }
        else if(INT_LOW_PRIORITY ==_eusart->usart_tx_cfg.priority){
            INT_GlobalInterruptLowEnable();
            EUSART_TX_LowPriorityset();
        }
#else
        INT_GlobalInterruptEnable();
        INT_PeripheralInterruptEnable();
#endif
#endif
}
    
    else if(EUSART_ASYNC_INTERRUPT_TX_DISABLE == _eusart->usart_tx_cfg.usart_tx_interrupt_enable){
        PIE1bits.TXIE = EUSART_ASYNC_INTERRUPT_TX_DISABLE;
    }
    else { }
    
    if(EUSART_ASYNC_9BIT_TX_ENABLE == _eusart->usart_tx_cfg.usart_tx_9bit_enable){
        TXSTAbits.TX9 = EUSART_ASYNC_9BIT_TX_ENABLE;
    }
    
    else if(EUSART_ASYNC_9BIT_TX_DISABLE == _eusart->usart_tx_cfg.usart_tx_9bit_enable){
        TXSTAbits.TX9 = EUSART_ASYNC_9BIT_TX_DISABLE;
    }
    else { }
    }
    
    
}

static void EUSART_ASYNC_RX_Init(const usart_t *_eusart){
    if(EUSART_ASYNC_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_enable){
        RCSTAbits.CREN = EUSART_ASYNC_RX_ENABLE;
        EUSART_RxInterruptHandler = _eusart->EUSART_RxDefaultInterruptHandler;
        EUSART_FramingErrorHandler = _eusart->EUSART_FramingErrorHandler;
        EUSART_OverrunErrorHandler = _eusart->EUSART_OverrunErrorHandler;
        
        if(EUSART_ASYNC_INTERRUPT_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_interrupt_enable){
        PIE1bits.RCIE = EUSART_ASYNC_INTERRUPT_RX_ENABLE;
        
#if EUSART_RX_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
        EUSART_RX_InterruptEnable();
#if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
        INT_PRIORITYLevelsEnable();

        if(INT_HIGH_PRIORITY ==_eusart->usart_rx_cfg.priority){
            INT_GlobalInterruptHighEnable();
            EUSART_TX_HighPriorityset();
        }
        else if(INT_LOW_PRIORITY ==_eusart->usart_rx_cfg.priority){
            INT_GlobalInterruptLowEnable();
            EUSART_RX_LowPriorityset();
        }
#else
        INT_GlobalInterruptEnable();
        INT_PeripheralInterruptEnable();
#endif
#endif
    }
    
    else if(EUSART_ASYNC_INTERRUPT_RX_DISABLE == _eusart->usart_rx_cfg.usart_rx_interrupt_enable){
        PIE1bits.RCIE = EUSART_ASYNC_INTERRUPT_RX_DISABLE;
    }
    else { }
    
    if(EUSART_ASYNC_9BIT_RX_ENABLE == _eusart->usart_rx_cfg.usart_rx_9bit_enable){
        RCSTAbits.RX9 = EUSART_ASYNC_9BIT_RX_ENABLE;
    }
    
    else if(EUSART_ASYNC_9BIT_RX_DISABLE == _eusart->usart_rx_cfg.usart_rx_9bit_enable){
        RCSTAbits.RX9 = EUSART_ASYNC_9BIT_RX_DISABLE;
    }
    else { }
    }
}

void EUSART_TX_ISR(void){
    PIE1bits.TXIE = 0;
    if(EUSART_TxInterruptHandler){
        EUSART_TxInterruptHandler();
    }
    else {
        
    }
}

void EUSART_RX_ISR(void){
    if(EUSART_RxInterruptHandler){
        EUSART_RxInterruptHandler();
    }
    else { }
    
    if(EUSART_FramingErrorHandler){
        EUSART_FramingErrorHandler();
    }
    else { }
    
    if(EUSART_OverrunErrorHandler){
        EUSART_OverrunErrorHandler();
    }
    else { }
}
