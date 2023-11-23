/* 
 * File:   HAL_GPIO.h
 * Author: Nadine
 *
 * Created on November 19, 2023, 1:46 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/* Section : Include */
#include <xc.h>
//#include <pic18f4620.h>
#include "../MCAL_STD_TYPES.h"
#include "../DEVICE_config.h"
#include "HAL_GPIO_config.h"

/*Section : Macro Declaration */
#define BIT_MASK  (u8) 1
#define PORT_MASK 0xFF

#define PORT_PIN_MAX_NUMBER 8
#define PORT_MAX_NUMBER     5

#define PORT_PIN_CONFIG    CONFIG_ENABLE
#define PORT_CONFIG        CONFIG_ENABLE

/*Section : Macro Function Declaration */
#define HWREGS(_X)                    (*((volatile u8 *)(_X)))

#define SET_BIT(REG, BIT_POS)         (REG |= (BIT_MASK << BIT_POS))
#define CLR_BIT(REG, BIT_POS)         (REG &= ~(BIT_MASK << BIT_POS))
#define TOG_BIT(REG, BIT_POS)         (REG ^= (BIT_MASK << BIT_POS))
#define READ_BIT(REG, BIT_POS)        ((REG << BIT_POS) & BIT_MASK)

/*Section : Datatype Declaration */
typedef enum {
    LOW,
    HIGH
}logic_t;

typedef enum {
    OUTPUT,
    INPUT
}direction_t;

typedef enum {
    PIN0_index,
    PIN1_index,
    PIN2_index,
    PIN3_index,
    PIN4_index,
    PIN5_index,
    PIN6_index,
    PIN7_index
}pin_index_t;

typedef enum {
    PORTA_index,
    PORTB_index,
    PORTC_index,
    PORTD_index,
    PORTE_index
}port_index_t;

typedef struct {
    u8 port : 3;
    u8 pin : 3;
    u8 direction : 1;
    u8 logic : 1;
}pin_config_t;

/*Section : Function Declaration */
Std_ReturnType GPIO_pin_dir_inti          (const pin_config_t *_pin_config_t);
Std_ReturnType GPIO_pin_get_dir_status    (const pin_config_t *_pin_config_t, direction_t *dir_status);
Std_ReturnType GPIO_pin_write_logic       (const pin_config_t *_pin_config_t, logic_t logic);
Std_ReturnType GPIO_pin_read_logic        (const pin_config_t *_pin_config_t, logic_t *logic);
Std_ReturnType GPIO_pin_tog_logic         (const pin_config_t *_pin_config_t);

Std_ReturnType GPIO_pin_inti          (const pin_config_t *_pin_config_t);

Std_ReturnType GPIO_port_dir_inti          (port_index_t port, u8 direction);
Std_ReturnType GPIO_port_get_dir_status    (port_index_t port, u8 *dir_status);
Std_ReturnType GPIO_port_write_logic    (port_index_t port, u8 logic);
Std_ReturnType GPIO_port_read_logic     (port_index_t port, u8 *logic);
Std_ReturnType GPIO_port_tog_logic     (port_index_t port);

#endif	/* HAL_GPIO_H */

