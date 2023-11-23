/* 
 * File:   ECU_BUTTON.c
 * Author: Nadine
 *
 * Created on November 19, 2023, 7:15 PM
 */

#include "ECU_BUTTON.h"

Std_ReturnType BUTTON_inti(const button_t *btn){
    
    Std_ReturnType ret = E_OK;
    
    if(NULL == btn) {
        ret = E_NOT_OK; }
    
    else {
        ret = GPIO_pin_dir_inti(&(btn->button_pin));
    }      
    return ret;
};

Std_ReturnType BUTTON_read(const button_t *btn, button_status_t *btn_state){
    
    Std_ReturnType ret = E_NOT_OK;
    logic_t btn_logic_status = LOW;
    
    if(NULL == btn  || NULL == btn_state) {
        ret = E_NOT_OK; }
    
    else {
        GPIO_pin_read_logic(&(btn->button_pin), &btn_logic_status);
        
        if (BUTTON_ACTIVE_HIGH == btn->button_connection) {
            
            if(HIGH == btn_logic_status) {
                *btn_state = BUTTON_PRESSED;
            }
            
            else { 
                *btn_state = BUTTON_RELEASED;
            }
            
        }
        
        else if (BUTTON_ACTIVE_LOW == btn->button_connection) {
            
            if(HIGH == btn_logic_status) {
                *btn_state = BUTTON_RELEASED;
            }
            
            else { 
                *btn_state = BUTTON_PRESSED;
            }
        
        }  
        
        else { /* nothing */ }
        ret = E_OK;
    }      
    return ret;
};