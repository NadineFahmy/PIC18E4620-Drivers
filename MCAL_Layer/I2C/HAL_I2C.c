/* 
 * File:   HAL_I2C.c
 * Author: Nadine
 *
 * Created on November 28, 2023, 1:31 PM
 */

#include "HAL_I2C.h"

#if MSSP_I2C_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
static void  (*I2C_Report_Write_Collision_InterruptHandler)(void) = NULL;
static void  (*I2C_DefaultInterruptHandler)(void) = NULL;
static void  (*I2C_Report_Receive_Overflow_InterruptHandler)(void) = NULL;
#endif

void MSSP_I2C_ISR(void);
void MSSP_I2C_BC_ISR(void);

static inline void MSSP_I2C_Mode_GPIO_CFG(void);
static inline void I2C__Master_Mode_CLK_CFG(const mssp_i2c_t *i2c_obj);
static inline void I2C_Interrput_CFG(const mssp_i2c_t *i2c_obj);
static inline void I2C_Slave_Mode_CFG(const mssp_i2c_t *i2c_obj);

Std_ReturnType MSSP_I2C_Init(const mssp_i2c_t *i2c_obj){
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == i2c_obj){
        ret = E_NOT_OK;
    }
    
    else { 
        MSSP_I2C_MODULE_DISABLE_CFG();
        
        if(i2c_obj->i2c_cfg.i2c_mode == MSSP_I2C_MASTER_MODE){
            I2C__Master_Mode_CLK_CFG(i2c_obj);
        }
        else if(i2c_obj->i2c_cfg.i2c_mode == MSSP_I2C_SLAVE_MODE){
            if(i2c_obj->i2c_cfg.i2c_general_call == I2C_GENREAL_CALL_ENABLE){
                I2C_GENREAL_CALL_ENABLE_CFG();
            }
            else if(i2c_obj->i2c_cfg.i2c_general_call == I2C_GENREAL_CALL_DISABLE){
                I2C_GENREAL_CALL_DISABLE_CFG();
            }
            else{ }
            
            SSPCON1bits.WCOL = 0 ;
            SSPCON1bits.SSPOV = 0 ;
            SSPCON1bits.CKP = 1 ;
            I2C_Slave_Mode_CFG(i2c_obj);
            
            SSPADD = i2c_obj->i2c_cfg.i2c_slave_address;
        }
        else{ }
        
        MSSP_I2C_Mode_GPIO_CFG();
        if(i2c_obj->i2c_cfg.i2c_slew_rate == I2C_SLEW_RATE_ENABLE){
                I2C_SLEW_RATE_ENABLE_CFG();
            }
        else if(i2c_obj->i2c_cfg.i2c_slew_rate == I2C_SLEW_RATE_DISABLE){
                I2C_SLEW_RATE_DISABLE_CFG();
            }
        else{ }
        
        
        if(i2c_obj->i2c_cfg.i2c_SMBus_control == I2C_SMBus_ENABLE){
                I2C_SMBus_ENABLE_CFG();
            }
        else if(i2c_obj->i2c_cfg.i2c_SMBus_control == I2C_SMBus_DISABLE){
                I2C_SMBus_DISABLE_CFG();
            }
        else{ }
        
#if MSSP_I2C_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
        I2C_Interrput_CFG(i2c_obj);
#endif
        
        MSSP_I2C_MODULE_ENABLE_CFG();
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType MSSP_I2C_DeInit(const mssp_i2c_t *i2c_obj){
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == i2c_obj){
        ret = E_NOT_OK;
    }
    
    else { 
        MSSP_I2C_MODULE_DISABLE_CFG();
#if MSSP_I2C_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
        MSSP_I2C_InterruptDisable();
        MSSP_I2C_BUS_COL_InterruptDisable();
#endif
        ret = E_OK;
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Send_Start(const mssp_i2c_t *i2c_obj){
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == i2c_obj){
        ret = E_NOT_OK;
    }
    
    else { 
        SSPCON2bits.SEN = 1;
        while(SSPCON2bits.SEN);
        PIR1bits.SSPIF = 0;
        
        if(START_BIT_DETECTED == SSPSTATbits.S){
            ret = E_OK;
        }
        else if(START_BIT_NOT_DETECTED == SSPSTATbits.S){
            ret = E_NOT_OK;
        }
        else { ret = E_NOT_OK; }
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Send_Reprated_Start(const mssp_i2c_t *i2c_obj){
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == i2c_obj){
        ret = E_NOT_OK;
    }
    
    else { 
       SSPCON2bits.RSEN = 1;
        while(SSPCON2bits.RSEN);
        PIR1bits.SSPIF = 0;
        ret = E_OK; 
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Send_Stop(const mssp_i2c_t *i2c_obj){
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == i2c_obj){
        ret = E_NOT_OK;
    }
    
    else { 
        SSPCON2bits.PEN = 1;
        while(SSPCON2bits.PEN);
        PIR1bits.SSPIF = 0;
        
        if(STOP_BIT_DETECTED == SSPSTATbits.S){
            ret = E_OK;
        }
        else if(STOP_BIT_NOT_DETECTED == SSPSTATbits.S){
            ret = E_NOT_OK;
        }
        else { ret = E_NOT_OK; }
    }
    return ret;
}

Std_ReturnType MSSP_I2C_Master_Write_Blocking(const mssp_i2c_t *i2c_obj, u8 data, u8 *_ack){
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == i2c_obj && NULL == _ack){
        ret = E_NOT_OK;
    }
    
    else { 
        SSPBUF = data;
        while(!PIR1bits.SSPIF);
        PIR1bits.SSPIF = 0;
        
        if(I2C_ACK_REC_FROM_SLAVE == SSPCON2bits.ACKSTAT){
            *_ack = I2C_ACK_REC_FROM_SLAVE;
        }
        else {
            *_ack = I2C_ACK_NOT_REC_FROM_SLAVE;
        }
        ret = E_OK;       
    }
    return ret;
}

Std_ReturnType MSSP_Master_I2C_Read_Blocking(const mssp_i2c_t *i2c_obj, u8 ack, u8 *data){
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == i2c_obj && NULL == data){
        ret = E_NOT_OK;
    }
    
    else { 
        I2C_MASTER_RECIEVE_ENABLE_CFG();
        while(!SSPSTATbits.BF);
        *data = SSPBUF;
        if(I2C_MASTER_SEND_ACK == ack){
            SSPCON2bits.ACKDT = 0;
            SSPCON2bits.ACKEN = 1;
        }
        else if(I2C_MASTER_SEND_NOT_ACK == ack){
            SSPCON2bits.ACKDT = 1;
            SSPCON2bits.ACKEN = 1;
        }
        else { }
        ret = E_OK;
    }
    return ret;
}

static inline void MSSP_I2C_Mode_GPIO_CFG(void){
    TRISCbits.TRISC3 = 1; /* SCL */
    TRISCbits.TRISC4 = 1; /* SDA */
}

static inline void I2C__Master_Mode_CLK_CFG(const mssp_i2c_t *i2c_obj){
    SSPCON1bits.SSPM = i2c_obj->i2c_cfg.i2c_mode_cfg;
    SSPADD = (u8)(((_XTAL_FREQ / 4.0) / i2c_obj->i2c_clk) - 1);
}

static inline void I2C_Slave_Mode_CFG(const mssp_i2c_t *i2c_obj){
    SSPCON1bits.SSPM = i2c_obj->i2c_cfg.i2c_mode_cfg;
}

static inline void I2C_Interrput_CFG(const mssp_i2c_t *i2c_obj){
    #if MSSP_I2C_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
        MSSP_I2C_InterruptEnable();
        MSSP_I2C_BUS_COL_InterruptEnable();
        
        MSSP_I2C_INTERRUPTFlagClear();
        MSSP_I2C_BUS_COL_INTERRUPTFlagClear();
        
        I2C_Report_Write_Collision_InterruptHandler = i2c_obj->I2C_Report_Write_Collision;
        I2C_DefaultInterruptHandler = i2c_obj->I2C_DefaultInterruptHandler;
        I2C_Report_Receive_Overflow_InterruptHandler = i2c_obj->I2C_Report_Receive_Overflow;
        
        #if INT_PRIORITY_Levels_Enable==INT_FEATURE_ENABLE
        INT_PRIORITYLevelsEnable();

        if(INT_HIGH_PRIORITY == i2c_obj->i2c_cfg.i2c_priority){
            INT_GlobalInterruptHighEnable();
            MSSP_I2C_HighPriorityset();
        }
        else if(INT_LOW_PRIORITY ==i2c_obj->i2c_cfg.i2c_priority){
            INT_GlobalInterruptLowEnable();
            MSSP_I2C_LowPriorityset();
        }
        else {}
        
        if(INT_HIGH_PRIORITY == i2c_obj->i2c_cfg.bus_col_priority){
            INT_GlobalInterruptHighEnable();
            MSSP_I2C_BUS_COL_HighPriorityset();
        }
        else if(INT_LOW_PRIORITY ==i2c_obj->i2c_cfg.bus_col_priority){
            INT_GlobalInterruptLowEnable();
            MSSP_I2C_BUS_COL_LowPriorityset();
        }
        else {}
        
        #else
        INT_GlobalInterruptEnable();
        INT_PeripheralInterruptEnable();
        #endif
        #endif
}

void MSSP_I2C_ISR(void){
#if MSSP_I2C_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
    MSSP_I2C_INTERRUPTFlagClear();
    if(I2C_DefaultInterruptHandler){
        I2C_DefaultInterruptHandler();
    }
#endif
}

void MSSP_I2C_BC_ISR(void){
#if MSSP_I2C_INT_FEATURE_ENABLE==INT_FEATURE_ENABLE
    MSSP_I2C_BUS_COL_INTERRUPTFlagClear();
    if(I2C_Report_Write_Collision_InterruptHandler){
        I2C_Report_Write_Collision_InterruptHandler();
    }
#endif
}
