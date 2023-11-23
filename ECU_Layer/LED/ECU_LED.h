/* 
 * File:   ECU_LED.h
 * Author: Nadine
 *
 * Created on November 19, 2023, 2:04 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section : Include */
#include "../../MCAL_Layer/GPIO/HAL_GPIO.h"
#include "ECU_LED_config.h"

/*Section : Datatype Declaration */
typedef enum {
    LED_OFF,
    LED_ON
}led_status_t;

typedef struct {
    u8 port_name : 4;
    u8 pin : 3;
    u8 led_status : 1;
}led_t;

/*Section : Function Declaration */
Std_ReturnType LED_inti(const led_t *led);
Std_ReturnType LED_turn_on(const led_t *led);
Std_ReturnType LED_turn_off(const led_t *led);
Std_ReturnType LED_tog(const led_t *led);

#endif	/* ECU_LED_H */

