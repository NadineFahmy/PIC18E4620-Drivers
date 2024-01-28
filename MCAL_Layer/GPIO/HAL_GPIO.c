/* 
 * File:   HAL_GPIO.c
 * Author: Nadine
 *
 * Created on November 19, 2023, 1:02 PM
 */

#include "HAL_GPIO.h"

volatile u8 *tris_register[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
volatile u8 *lat_register[] = {&LATA, &LATB, &LATC, &LATD, &LATE};
volatile u8 *port_register[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};

Std_ReturnType GPIO_pin_dir_inti(const pin_config_t *_pin_config_t){
    
    Std_ReturnType ret = E_OK;
    
    if(NULL == _pin_config_t || _pin_config_t->pin > PORT_PIN_MAX_NUMBER - 1) {
        ret = E_NOT_OK; }
    
    else {
       switch(_pin_config_t->direction) {
        case OUTPUT :
            CLR_BIT(*tris_register[_pin_config_t->port], _pin_config_t->pin);
            break;
            
        case INPUT :
            SET_BIT(*tris_register[_pin_config_t->port], _pin_config_t->pin);
            break;
           
        default : ret = E_NOT_OK;
        }        
    }
    return ret;
}

Std_ReturnType GPIO_pin_get_dir_status(const pin_config_t *_pin_config_t, direction_t *dir_status) {
    
    Std_ReturnType ret = E_OK;
    
    if(NULL == _pin_config_t || NULL == dir_status || _pin_config_t->pin > PORT_PIN_MAX_NUMBER - 1) {
        ret = E_NOT_OK;
    }
    
    else {
        *dir_status = READ_BIT(*tris_register[_pin_config_t->port], _pin_config_t->pin);
    }
    return ret;
}

Std_ReturnType GPIO_pin_write_logic(const pin_config_t *_pin_config_t, logic_t logic) {
    
    Std_ReturnType ret = E_OK;
    
    if(NULL == _pin_config_t || _pin_config_t->pin > PORT_PIN_MAX_NUMBER - 1) {
        ret = E_NOT_OK; 
    }
    
    else {
       switch(logic) {
        case LOW :
            CLR_BIT(*lat_register[_pin_config_t->port], _pin_config_t->pin);
            break;
            
        case HIGH :
            SET_BIT(*lat_register[_pin_config_t->port], _pin_config_t->pin);
            break;
           
        default : ret = E_NOT_OK;
        }        
    }
    return ret;
}

Std_ReturnType GPIO_pin_read_logic(const pin_config_t *_pin_config_t, logic_t *logic) {
    
    Std_ReturnType ret = E_OK;
    
    if(NULL == _pin_config_t || NULL == logic || _pin_config_t->pin > PORT_PIN_MAX_NUMBER - 1) {
        ret = E_NOT_OK;
    }
    else {
        *logic = READ_BIT(*port_register[_pin_config_t->port], _pin_config_t->pin);
    }
    return ret;
}

Std_ReturnType GPIO_pin_tog_logic(const pin_config_t *_pin_config_t) {
    
    Std_ReturnType ret = E_OK;
    
    if(NULL == _pin_config_t || _pin_config_t->pin > PORT_PIN_MAX_NUMBER - 1) {
        ret = E_NOT_OK;
    }
    else {
        TOG_BIT(*lat_register[_pin_config_t->port], _pin_config_t->pin);
    }
    return ret;
}

Std_ReturnType GPIO_pin_inti(const pin_config_t *_pin_config_t){
    Std_ReturnType ret = E_OK;
    
    if(NULL == _pin_config_t || _pin_config_t->pin > PORT_PIN_MAX_NUMBER - 1) {
        ret = E_NOT_OK;
    }
    else {
        ret = GPIO_pin_dir_inti(_pin_config_t);
        ret = GPIO_pin_write_logic(_pin_config_t, _pin_config_t->logic);
    }
    return ret;
}



Std_ReturnType GPIO_port_dir_inti(port_index_t port, u8 direction) {
    
    Std_ReturnType ret = E_OK;
    
    if(port > PORT_MAX_NUMBER - 1) {
        ret = E_NOT_OK;
    }
    else {
        *tris_register[port] = direction;
    }
    return ret;
}

Std_ReturnType GPIO_port_get_dir_status(port_index_t port, u8 *dir_status) {
    
    Std_ReturnType ret = E_OK;
    
    if((NULL == dir_status) && (port > PORT_MAX_NUMBER - 1)) {
        ret = E_NOT_OK;
    }
    else {
        *dir_status = *tris_register[port];
    }
    return ret;
}

Std_ReturnType GPIO_port_write_logic(port_index_t port, u8 logic) {
    
    Std_ReturnType ret = E_OK;
    
    if(port > PORT_MAX_NUMBER - 1) {
        ret = E_NOT_OK;
    }
    else {
        *lat_register[port] = logic;
    }
    return ret;
}

Std_ReturnType GPIO_port_read_logic(port_index_t port, u8 *logic) {
    
    Std_ReturnType ret = E_OK;
    
    if((NULL == logic) && (port > PORT_MAX_NUMBER - 1)) {
        ret = E_NOT_OK;
    }
    else {
        *logic = *lat_register[port];
    }
    return ret;
}

Std_ReturnType GPIO_port_tog_logic(port_index_t port){
    
    Std_ReturnType ret = E_OK;
    
    if(port > PORT_MAX_NUMBER - 1) {
        ret = E_NOT_OK;
    }
    else {
        *lat_register[port] = *lat_register[port] ^ PORT_MASK;
    }
    return ret;
}
