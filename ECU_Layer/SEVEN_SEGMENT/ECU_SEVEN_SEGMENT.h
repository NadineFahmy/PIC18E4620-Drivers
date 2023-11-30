/* 
 * File:   ECU_SEVEN_SEGMENT.h
 * Author: Nadine
 *
 * Created on November 29, 2023, 4:04 PM
 */

#ifndef ECU_SEVEN_SEGMENT_H
#define	ECU_SEVEN_SEGMENT_H

#include "ECU_SEVEN_SEGMENT_config.h"
#include "../../MCAL_Layer/GPIO/HAL_GPIO.h"

typedef enum {
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE
}segment_type_t;

typedef struct {
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
}segment_t;


Std_ReturnType SEVEN_SEGMENT_inti(const segment_t *segment);
Std_ReturnType SEVEN_SEGMENT_write_number(const segment_t *segment, u8 number);

#endif	/* ECU_SEVEN_SEGMENT_H */

