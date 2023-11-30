/* 
 * File:   ECU_DC_MOTOR.h
 * Author: Nadine
 *
 * Created on November 29, 2023, 2:34 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

#include "ECU_DC_MOTOR_config.h"
#include "../../MCAL_Layer/GPIO/HAL_GPIO.h"

#define DC_MOTOR_ON_STATUS  0x01U
#define DC_MOTOR_OFF_STATUS 0x00U

typedef struct{
    pin_config_t dc_motor_pin[2];
}dc_motor_t;

Std_ReturnType DC_MOTOR_inti(const dc_motor_t *dc_motor);
Std_ReturnType DC_MOTOR_Move_Right(const dc_motor_t *dc_motor);
Std_ReturnType DC_MOTOR_Move_Left(const dc_motor_t *dc_motor);
Std_ReturnType DC_MOTOR_Stop(const dc_motor_t *dc_motor);
#endif	/* ECU_DC_MOTOR_H */

