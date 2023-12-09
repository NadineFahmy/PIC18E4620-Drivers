/* 
 * File:   HAL_I2C.h
 * Author: Nadine
 *
 * Created on November 28, 2023, 1:31 PM
 */

#ifndef HAL_I2C_H
#define	HAL_I2C_H

/* Section : Include */
#include <xc.h>
//#include <pic18f4620.h>
#include "../MCAL_STD_TYPES.h"
#include "../GPIO/HAL_GPIO.h"
#include "../INTERRUPT/MCAL_INTERNAL_INTERRUPT.h"

/*Section : Macro Declaration */
#define I2C_SLEW_RATE_DISABLE 1
#define I2C_SLEW_RATE_ENABLE  0

#define I2C_SMBus_ENABLE  1
#define I2C_SMBus_DISABLE 0

#define I2C_LAST_BYTE_DATA    1
#define I2C_LAST_BYTE_ADDRESS 0

#define STOP_BIT_DETECTED     1
#define STOP_BIT_NOT_DETECTED 0

#define START_BIT_DETECTED     1
#define START_BIT_NOT_DETECTED 0

#define MSSP_I2C_MASTER_MODE    1
#define MSSP_I2C_SLAVE_MODE     0

#define I2C_SLAVE_MODE_7BIT_ADDRESS                0x06U
#define I2C_SLAVE_MODE_10BIT_ADDRESS               0x07U
#define I2C_SLAVE_MODE_7BIT_ADDRESS_SS_INT_ENABLE  0x0EU
#define I2C_SLAVE_MODE_10BIT_ADDRESS_SS_INT_ENABLE 0x0FU
#define I2C_MASTER_MODE_DEFINED_CLK                0x08U
#define I2C_MASTER_MODE_FRIMWARE_CONTROLLED        0x0BU

#define I2C_GENREAL_CALL_ENABLE  1
#define I2C_GENREAL_CALL_DISABLE 0

#define I2C_MASTER_RECIEVE_ENABLE  1
#define I2C_MASTER_RECIEVE_DISABLE 0

#define I2C_ACK_REC_FROM_SLAVE      0
#define I2C_ACK_NOT_REC_FROM_SLAVE  1

#define I2C_MASTER_SEND_ACK      0
#define I2C_MASTER_SEND_NOT_ACK  1


/*Section : Macro Function Declaration */
#define I2C_SLEW_RATE_DISABLE_CFG() (SSPSTATbits.SMP = 1)
#define I2C_SLEW_RATE_ENABLE_CFG()  (SSPSTATbits.SMP = 0)

#define I2C_SMBus_DISABLE_CFG()  (SSPSTATbits.CKE = 0)
#define I2C_SMBus_ENABLE_CFG()   (SSPSTATbits.CKE = 1)

#define I2C_GENREAL_CALL_DISABLE_CFG()  (SSPCON2bits.GCEN = 0)
#define I2C_GENREAL_CALL_ENABLE_CFG()   (SSPCON2bits.GCEN = 1)

#define I2C_MASTER_RECIEVE_DISABLE_CFG()  (SSPCON2bits.RCEN = 0)
#define I2C_MASTER_RECIEVE_ENABLE_CFG()   (SSPCON2bits.RCEN = 1)

#define MSSP_I2C_MODULE_ENABLE_CFG()  (SSPCON1bits.SSPEN = 1)
#define MSSP_I2C_MODULE_DISABLE_CFG() (SSPCON1bits.SSPEN = 0)

#define I2C_CLOCK_STRECH_ENABLE()    (SSPCON1bits.CKP = 0)
#define I2C_CLOCK_STRECH_DISABLE()    (SSPCON1bits.CKP = 1)

/*Section : Datatype Declaration */
typedef struct{
#if MSSP_I2C_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
   INT_priority_cfg i2c_priority;
   INT_priority_cfg bus_col_priority;
#endif
    u8 i2c_mode_cfg;
    u8 i2c_slave_address;
    u8 i2c_mode: 1;
    u8 i2c_slew_rate: 1;
    u8 i2c_SMBus_control: 1 ;
    u8 i2c_general_call: 1;
    u8 i2c_master_rec_mode: 1 ;
    u8 i2c_reserved: 3 ;   
} i2c_config_t;

typedef struct{
   u8 i2c_clk;
#if MSSP_I2C_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
   void(* I2C_Report_Write_Collision)(void);
   void(* I2C_Report_Receive_Overflow)(void);
   void(* I2C_DefaultInterruptHandler)(void);
#endif
   i2c_config_t i2c_cfg;
}mssp_i2c_t;

/*Section : Function Declaration */
Std_ReturnType MSSP_I2C_Init(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_DeInit(const mssp_i2c_t *i2c_obj);

Std_ReturnType MSSP_I2C_Master_Send_Start(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Reprated_Start(const mssp_i2c_t *i2c_obj);
Std_ReturnType MSSP_I2C_Master_Send_Stop(const mssp_i2c_t *i2c_obj);

Std_ReturnType MSSP_I2C_Master_Write_Blocking(const mssp_i2c_t *i2c_obj, u8 data, u8 *_ack);
Std_ReturnType MSSP_I2C_Master_Read_Blocking(const mssp_i2c_t *i2c_obj, u8 ack, u8 *data);




#endif	/* HAL_I2C_H */

