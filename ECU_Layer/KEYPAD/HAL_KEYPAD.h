/* 
 * File:   HAL_KEYPAD.h
 * Author: Nadine
 *
 * Created on November 30, 2023, 12:44 PM
 */

#ifndef HAL_KEYPAD_H
#define	HAL_KEYPAD_H

#include "HAL_KEYPAD_config.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

#define ECU_KEYPAD_ROWS    4
#define ECU_KEYPAD_COLUMNS 4 

typedef struct{
    pin_config_t keypad_row_pins[ECU_KEYPAD_ROWS];
    pin_config_t keypad_columns_pins[ECU_KEYPAD_COLUMNS];
}keypad_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType KEYPAD_init(const keypad_t *_keypad_obj);
Std_ReturnType KEYPAD_get_value(const keypad_t *_keypad_obj, u8 *value);

#endif	/* HAL_KEYPAD_H */

