/* 
 * File:   ECU_LED.c
 * Author: Nadine
 *
 * Created on November 19, 2023, 1:46 PM
 */

#include "ECU_LED.h"

Std_ReturnType LED_inti(const led_t *led){
    
    Std_ReturnType ret = E_OK;
    
    if(NULL == led) {
        ret = E_NOT_OK; }
    
    else {
        
        pin_config_t pin_obj = {
            .port = led ->port_name,
            .pin = led->pin,
            .direction = OUTPUT,
            .logic = led->led_status
        };
        
        GPIO_pin_inti(&pin_obj);
    }      
    return ret;
};

Std_ReturnType LED_turn_on(const led_t *led){
    
    Std_ReturnType ret = E_OK;
    
    if(NULL == led) {
        ret = E_NOT_OK; }
    
    else {
        pin_config_t pin_obj = {
            .port = led ->port_name, 
            .pin = led->pin,
            .direction = OUTPUT,
            .logic = led->led_status
        };
        
        GPIO_pin_write_logic(&pin_obj, HIGH);
        
    }      
    return ret;
};

Std_ReturnType LED_turn_off(const led_t *led){
    
    Std_ReturnType ret = E_OK;
    
    if(NULL == led) {
        ret = E_NOT_OK; }
    
    else {
         pin_config_t pin_obj = {
            .port = led ->port_name, 
            .pin = led->pin,
            .direction = OUTPUT,
            .logic = led->led_status
         };
        
        GPIO_pin_write_logic(&pin_obj, LOW);
    }      
    return ret;
};

Std_ReturnType LED_tog(const led_t *led){
    
    Std_ReturnType ret = E_OK;
    
    if(NULL == led) {
        ret = E_NOT_OK; }
    
    else {
         pin_config_t pin_obj = {
            .port = led ->port_name, 
            .pin = led->pin,
            .direction = OUTPUT,
            .logic = led->led_status
         };
        
        GPIO_pin_tog_logic (&pin_obj);
    }      
    return ret;
};