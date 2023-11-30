/* 
 * File:   ECU_RELAY.h
 * Author: Nadine
 *
 * Created on November 29, 2023, 12:24 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

#include "ECU_RELAY_config.h"
#include "../../MCAL_Layer/GPIO/HAL_GPIO.h"

#define RELAY_ON_STATUS  0x01U
#define RELAY_OFF_STATUS 0x00U

typedef struct{
    u8 relay_port: 4;
    u8 relay_pin: 3;
    u8 relay_status: 1;
}relay_t;

Std_ReturnType RELAY_inti(const relay_t *relay);
Std_ReturnType RELAY_turn_on(const relay_t *relay);
Std_ReturnType RELAY_turn_off(const relay_t *relay);
Std_ReturnType RELAY_tog(const relay_t *relay);


#endif	/* ECU_RELAY_H */

