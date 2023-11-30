/* 
 * File:   ECU_SEVEN_SEGMENT.c
 * Author: Nadine
 *
 * Created on November 29, 2023, 4:04 PM
 */

#include "ECU_SEVEN_SEGMENT.h"

Std_ReturnType SEVEN_SEGMENT_inti(const segment_t *segment){
    
    Std_ReturnType ret = E_OK;
    
    if(NULL == segment) {
        ret = E_NOT_OK; }
    
    else {  
        ret = GPIO_pin_inti( &(segment->segment_pins[0]) );
        ret = GPIO_pin_inti( &(segment->segment_pins[1]) );
        ret = GPIO_pin_inti( &(segment->segment_pins[2]) );
        ret = GPIO_pin_inti( &(segment->segment_pins[3]) );
    }
    return ret;
};

Std_ReturnType SEVEN_SEGMENT_write_number(const segment_t *segment, u8 number){
    
    Std_ReturnType ret = E_OK;
    
    if( (NULL == segment) && (number > 9) ) {
        ret = E_NOT_OK; }
    
    else {  
        ret = GPIO_pin_write_logic( &(segment->segment_pins[0]), (number & 0x01) );
        ret = GPIO_pin_write_logic( &(segment->segment_pins[1]), ( (number >> 1) & 0x01) );
        ret = GPIO_pin_write_logic( &(segment->segment_pins[2]), ( (number >> 2) & 0x01) );
        ret = GPIO_pin_write_logic( &(segment->segment_pins[3]), ( (number >> 3) & 0x01) );
    }
    return ret;
};