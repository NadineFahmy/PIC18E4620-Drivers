/* 
 * File:   HAL_KEYPAD.c
 * Author: Nadine
 *
 * Created on November 30, 2023, 12:44 PM
 */

#include "HAL_KEYPAD.h"

static const u8 btn_values[ECU_KEYPAD_ROWS][ECU_KEYPAD_COLUMNS] = {
                                                                        {'7', '8', '9', '/'},
                                                                        {'4', '5', '6', '*'},
                                                                        {'1', '2', '3', '-'},
                                                                        {'#', '0', '=', '+'}
                                                                     };

Std_ReturnType keypad_init(const keypad_t *_keypad_obj){
    Std_ReturnType ret = E_OK;
    u8 rows_counter = 0, columns_counter = 0;
    if(NULL == _keypad_obj){
        ret = E_NOT_OK;
    }
    else{    
        for(rows_counter=0; rows_counter<ECU_KEYPAD_ROWS; rows_counter++){
            ret = GPIO_pin_inti(&(_keypad_obj->keypad_row_pins[rows_counter]));
        }
        for(columns_counter=0; columns_counter<ECU_KEYPAD_COLUMNS; columns_counter++){
            ret = GPIO_pin_dir_inti(&(_keypad_obj->keypad_columns_pins[columns_counter]));
        }
    }
    return ret;
}

Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, u8 *value){
    Std_ReturnType ret = E_OK;
    u8 l_rows_counter = 0, l_columns_counter = 0, l_counter = 0;
    u8 column_logic = 0;
    if((NULL == _keypad_obj) || (NULL == value)){
        ret = E_NOT_OK;
    }
    else{    
        for(l_rows_counter=0; l_rows_counter<ECU_KEYPAD_ROWS; l_rows_counter++){
            for(l_counter=0; l_counter<ECU_KEYPAD_ROWS; l_counter++){
                ret = GPIO_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_counter]), LOW);
            }
            GPIO_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_rows_counter]), HIGH);
            __delay_ms(10);
            for(l_columns_counter=0; l_columns_counter<ECU_KEYPAD_COLUMNS; l_columns_counter++){
                ret = GPIO_pin_read_logic(&(_keypad_obj->keypad_columns_pins[l_columns_counter]), &column_logic);
                if(HIGH == column_logic){
                    *value = btn_values[l_rows_counter][l_columns_counter];
                }
            }
        }
    }
    return ret;
}

