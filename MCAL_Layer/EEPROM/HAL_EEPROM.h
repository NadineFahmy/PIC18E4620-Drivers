/* 
 * File:   HAL_EEPROM.h
 * Author: Nadine
 *
 * Created on December 1, 2023, 3:35 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

#include <xc.h>
//#include <pic18f4620.h>
#include "../MCAL_STD_TYPES.h"
#include "../../MCAL_Layer/INTERRUPT/MCAL_INTERNAL_INTERRUPT.h"

/* Flash Program or Data EEPROM Memory Select  */
#define ACCESS_FLASH_PROGRAM_MEMORY       1
#define ACCESS_EEPROM_PROGRAM_MEMORY      0
/* Flash Program/Data EEPROM or Configuration Select */
#define ACCESS_CONFIG_REGISTERS           1
#define ACCESS_FLASH_EEPROM_MEMORY        0
/* Flash Program/Data EEPROM Write Enable */
#define ALLOW_WRITE_CYCLES_FLASH_EEPROM   1
#define INHIBTS_WRITE_CYCLES_FLASH_EEPROM 0
/* Write Control */
#define INITIATE_DATA_EEPROM_WRITE_ERASE  1
#define DATA_EEPROM_WRITE_ERASE_COMPLETED 0
/* Read Control */
#define INITIATE_DATA_EEPROM_READ         1


Std_ReturnType Data_EEPROM_WriteByte(u16 bAdd, u8 bData);
Std_ReturnType Data_EEPROM_ReadByte(u16 bAdd, u8 *bData);

#endif	/* HAL_EEPROM_H */

