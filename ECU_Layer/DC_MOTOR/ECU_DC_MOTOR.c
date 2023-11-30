/* 
 * File:   ECU_DC_MOTOR.c
 * Author: Nadine
 *
 * Created on November 29, 2023, 2:34 PM
 */

#include "ECU_DC_MOTOR.h"
static pin_config_t pin_obj1;
static pin_config_t pin_obj2;

Std_ReturnType DC_MOTOR_inti(const dc_motor_t *dc_motor){
    Std_ReturnType ret = E_OK;
    
    if(NULL == dc_motor) {
        ret = E_NOT_OK; }
    
    else {  
        GPIO_pin_inti(&(dc_motor->dc_motor_pin[0]));
        GPIO_pin_inti(&(dc_motor->dc_motor_pin[1]));
    }
    return ret;
};

Std_ReturnType DC_MOTOR_Move_Right(const dc_motor_t *dc_motor){
    Std_ReturnType ret = E_OK;
    
    if(NULL == dc_motor) {
        ret = E_NOT_OK; }
    
    else {
        GPIO_pin_write_logic(&(dc_motor->dc_motor_pin[0]), HIGH);
        GPIO_pin_write_logic(&(dc_motor->dc_motor_pin[1]), LOW);
    }
    return ret;
};

Std_ReturnType DC_MOTOR_Move_Left(const dc_motor_t *dc_motor){
    Std_ReturnType ret = E_OK;
    
    if(NULL == dc_motor) {
        ret = E_NOT_OK; }
    
    else {
        GPIO_pin_write_logic(&(dc_motor->dc_motor_pin[0]), LOW);
        GPIO_pin_write_logic(&(dc_motor->dc_motor_pin[1]), HIGH);
    }
    return ret;
};

Std_ReturnType DC_MOTOR_Stop(const dc_motor_t *dc_motor){
    Std_ReturnType ret = E_OK;
    
    if(NULL == dc_motor) {
        ret = E_NOT_OK; }
    
    else {
        GPIO_pin_write_logic(&(dc_motor->dc_motor_pin[0]), LOW);
        GPIO_pin_write_logic(&(dc_motor->dc_motor_pin[1]), LOW);
    }
    return ret;
};