/* 
 * File:   ECU_RELAY.c
 * Author: Nadine
 *
 * Created on November 29, 2023, 12:24 PM
 */

#include "ECU_RELAY.h"

Std_ReturnType RELAY_inti(const relay_t *relay){
    Std_ReturnType ret = E_OK;
    
    if(NULL == relay) {
        ret = E_NOT_OK; }
    
    else {
        pin_config_t pin_obj = {
            .port = relay ->relay_port,
            .pin = relay->relay_pin,
            .direction = OUTPUT,
            .logic = relay->relay_status
        }
        
        GPIO_pin_inti(&pin_obj);
    }     
    return ret;
}

Std_ReturnType RELAY_turn_on(const relay_t *relay){
    Std_ReturnType ret = E_OK;
    
    if(NULL == relay) {
        ret = E_NOT_OK; }
    
    else {
        pin_config_t pin_obj = {
            .port = relay ->relay_port,
            .pin = relay->relay_pin,
            .direction = OUTPUT,
            .logic = relay->relay_status
        }
        
        GPIO_pin_write_logic(&pin_obj, HIGH);
    }     
    return ret;
}

Std_ReturnType RELAY_turn_off(const relay_t *relay){
    Std_ReturnType ret = E_OK;
    
    if(NULL == relay) {
        ret = E_NOT_OK; }
    
    else {
        pin_config_t pin_obj = {
            .port = relay->relay_port, 
            .pin = relay->relay_pin,
            .direction = OUTPUT,
            .logic = relay->relay_status
         }
        
        GPIO_pin_write_logic(&pin_obj, LOW);
    }     
    return ret;
}

Std_ReturnType RELAY_tog(const relay_t *relay){
    Std_ReturnType ret = E_OK;
    
    if(NULL == relay) {
        ret = E_NOT_OK; }
    
    else {
        pin_config_t pin_obj = {
            .port = relay ->relay_port, 
            .pin = relay->relay_pin,
            .direction = OUTPUT,
            .logic = relay->relay_status
         }
        
        GPIO_pin_tog_logic (&pin_obj);
    }     
    return ret;
}
