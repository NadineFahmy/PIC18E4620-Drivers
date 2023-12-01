/* 
 * File:   HAL_EEPROM.c
 * Author: Nadine
 *
 * Created on December 1, 2023, 3:35 PM
 */
#include "HAL_EEPROM.h"


Std_ReturnType Data_EEPROM_WriteByte(u16 bAdd, u8 bData){
    Std_ReturnType ret = E_OK;
    /* Read the Interrupt Status "Enabled or Disabled" */
    u8 Global_Interrupt_Status = INTCONbits.GIE;
    /* Update the Address Registers */
    EEADRH = (u8)((bAdd >> 8) & 0x03);
    EEADR = (u8)(bAdd & 0xFF);
    /* Update the Data Register */
    EEDATA = bData;
    /* Select Access data EEPROM memory */
    EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
    EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
    /* Allows write cycles to Flash program/data EEPROM */
    EECON1bits.WREN = ALLOW_WRITE_CYCLES_FLASH_EEPROM;
    /* Disable all interrupts "General Interrupt" */
    //INT_GlobalInterruptDisable();
    /* Write the required sequence : 0x55 -> 0xAA */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /* Initiates a data EEPROM erase/write cycle */
    EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;
    /* Wait for write to complete */
    while(EECON1bits.WR);
    /* Inhibits write cycles to Flash program/data EEPROM */
    EECON1bits.WREN = INHIBTS_WRITE_CYCLES_FLASH_EEPROM;
    /* Restore the Interrupt Status "Enabled or Disabled" */
    INTCONbits.GIE = Global_Interrupt_Status;
    return ret;
}

Std_ReturnType Data_EEPROM_ReadByte(u16 bAdd, u8 *bData){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == bData){
        ret = E_NOT_OK;
    }
    else{
        /* Update the Address Registers */
        EEADRH = (u8)((bAdd >> 8) & 0x03);
        EEADR = (u8)(bAdd & 0xFF);
        /* Select Access data EEPROM memory */
        EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
        EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
        /* Initiates a data EEPROM read cycle */
        EECON1bits.RD = INITIATE_DATA_EEPROM_READ;
        NOP(); /* NOPs may be required for latency at high frequencies */
        NOP(); /* NOPs may be required for latency at high frequencies */
        /* Return data */
        *bData = EEDATA;
        ret = E_OK;
    }
    return ret;
}
