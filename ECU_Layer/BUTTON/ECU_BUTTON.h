/* 
 * File:   ECU_BUTTON.h
 * Author: Nadine
 *
 * Created on November 19, 2023, 7:15 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/* Section : Include */
#include "../../MCAL_Layer/GPIO/HAL_GPIO.h"
#include "ECU_BUTTON_config.h"

/*Section : Datatype Declaration */
typedef enum {
    BUTTON_PRESSED,
    BUTTON_RELEASED
}button_status_t;

typedef enum {
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW
}button_active_t;

typedef struct {
    pin_config_t button_pin;
    button_status_t button_state;
    button_active_t button_connection;
}button_t;

/*Section : Function Declaration */
Std_ReturnType BUTTON_inti(const button_t *btn);
Std_ReturnType BUTTON_read(const button_t *btn, button_status_t *btn_state);
        
#endif	/* ECU_BUTTON_H */

