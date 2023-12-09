/* 
 * File:   HAL_USART.h
 * Author: Nadine
 *
 * Created on November 26, 2023, 7:15 PM
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

/* Section : Include */
#include <xc.h>
//#include <pic18f4620.h>
#include "../MCAL_STD_TYPES.h"
#include "../GPIO/HAL_GPIO.h"
#include "HAL_USART_cfg.h"
#include "../INTERRUPT/MCAL_INTERNAL_INTERRUPT.h"

/*Section : Macro Declaration */
#define EUSART_MODULE_ENABLE 1
#define EUSART_MODULE_DISABLE 0

#define EUSART_SYNC_MODE 1
#define EUSART_ASYNC_MODE 0

#define EUSART_ASYNC_HIGH_SPEED 1
#define EUSART_ASYNC_LOW_SPEED 0

#define EUSART_16BIT_BAUDRATE_GEN 1
#define EUSART_08BIT_BAUDRATE_GEN 0

#define EUSART_ASYNC_TX_ENABLE  1
#define EUSART_ASYNC_TX_DISABLE 0

#define EUSART_ASYNC_INTERRUPT_TX_ENABLE  1
#define EUSART_ASYNC_INTERRUPT_TX_DISABLE 0

#define EUSART_ASYNC_9BIT_TX_ENABLE   1
#define EUSART_ASYNC_9BIT_TX_DISABLE  0

#define EUSART_ASYNC_RX_ENABLE  1
#define EUSART_ASYNC_RX_DISABLE 0

#define EUSART_ASYNC_INTERRUPT_RX_ENABLE  1
#define EUSART_ASYNC_INTERRUPT_RX_DISABLE 0

#define EUSART_ASYNC_9BIT_RX_ENABLE   1
#define EUSART_ASYNC_9BIT_RX_DISABLE  0

#define EUSART_FRAMING_ERROR_DETECTED 1
#define EUSART_FRAMING_ERROR_CLEARED  0

#define EUSART_OVERRUN_ERROR_DETECTED 1
#define EUSART_OVERRUN_ERROR_CLEARED  0

/*Section : Macro Function Declaration */

/*Section : Datatype Declaration */
typedef enum{
    BAUDRATE_ASYNC_8BIT_LOW_SPEED,
    BAUDRATE_ASYNC_8BIT_HIGH_SPEED,
    BAUDRATE_ASYNC_16BIT_LOW_SPEED,
    BAUDRATE_ASYNC_16BIT_HIGH_SPEED,
    BAUDRATE_SYNC_8BIT,
    BAUDRATE_SYNC_16BIT
}baudrate_gen_t;

typedef struct{
    u8 usart_tx_reserved: 5;
    u8 usart_tx_enable: 1;
    u8 usart_tx_interrupt_enable: 1;
    u8 usart_tx_9bit_enable: 1;
    INT_priority_cfg priority;
}usart_tx_cfg_t;

typedef struct{
    u8 usart_rx_reserved: 5;
    u8 usart_rx_enable: 1;
    u8 usart_rx_interrupt_enable: 1;
    u8 usart_rx_9bit_enable: 1;
    INT_priority_cfg priority;
}usart_rx_cfg_t;

typedef union{
    struct{
        u8 usart_tx_reserved: 5;
        u8 usart_ferr: 1;
        u8 usart_oerr: 1;
    };
    u8 satus;
}usart_error_status_t;

typedef struct{
    u32 baudrate;
    baudrate_gen_t baudrate_gen_cfg;
    usart_tx_cfg_t usart_tx_cfg;
    usart_rx_cfg_t usart_rx_cfg;
    usart_error_status_t usart_error_status;
    void(* EUSART_TxDefaultInterruptHandler)(void);
    void(* EUSART_RxDefaultInterruptHandler)(void);
    void(* EUSART_FramingErrorHandler)(void);
    void(* EUSART_OverrunErrorHandler)(void);
}usart_t;

/*Section : Function Declaration */
Std_ReturnType EUSART_ASYNC_Init(const usart_t *_eusart);
Std_ReturnType EUSART_ASYNC_DeInit(const usart_t *_eusart);

Std_ReturnType EUSART_ASYNC_ReadByteBlocking(u8 *_data);
Std_ReturnType EUSART_ASYNC_ReadNonByteBlocking(u8 *_data);
Std_ReturnType EUSART_ASYNC_Restart_RX(void);

Std_ReturnType EUSART_ASYNC_WriteByteBlockinge(u8 _data);
Std_ReturnType EUSART_ASYNC_WriteStringBlockinge(u8 *_data, u16 str_length);

Std_ReturnType EUSART_ASYNC_WriteByteNonBlockinge(u8 _data);
Std_ReturnType EUSART_ASYNC_WriteStringNonBlockinge(u8 *_data, u16 str_length);

#endif	/* HAL_USART_H */

