/* 
 * File:   HAL_CLCD.h
 * Author: Nadine
 *
 * Created on November 30, 2023, 3:02 PM
 */

#ifndef HAL_CLCD_H
#define	HAL_CLCD_H

#include "HAL_CLCD_config.h"
#include "../../MCAL_Layer/GPIO/HAL_GPIO.h"

#define _LCD_CLEAR                      0X01
#define _LCD_RETURN_HOME                0x02
#define _LCD_ENTRY_MODE_DEC_SHIFT_OFF   0x04
#define _LCD_ENTRY_MODE_DEC_SHIFT_ON    0x05
#define _LCD_ENTRY_MODE_INC_SHIFT_OFF   0x06
#define _LCD_ENTRY_MODE_INC_SHIFT_ON    0x07
#define _LCD_CURSOR_MOVE_SHIFT_LEFT     0x10
#define _LCD_CURSOR_MOVE_SHIFT_RIGHT    0x14
#define _LCD_DISPLAY_SHIFT_LEFT         0x18
#define _LCD_DISPLAY_SHIFT_RIGHT        0x1C
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF 0x0C
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON  0x0D
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF  0x0E
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON   0x0F
#define _LCD_DISPLAY_OFF_CURSOR_OFF              0x08
#define _LCD_8BIT_MODE_2_LINE           0x38
#define _LCD_4BIT_MODE_2_LINE           0x28

#define _LCD_CGRAM_START                0x40
#define _LCD_DDRAM_START                0x80

#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4

typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];
}chr_lcd_4bit_t;

typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];
}chr_lcd_8bit_t;

Std_ReturnType lcd_4bit_intialize(const chr_lcd_4bit_t *lcd);
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd, u8 command);
Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd, u8 data);
Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd,u8 row, u8 column, u8 data);
Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd, u8 *str);
Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd, u8 row, u8 column, u8 *str);
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, u8 row, u8 column, 
                                         const u8 _chr[], u8 mem_pos);

Std_ReturnType lcd_8bit_intialize(const chr_lcd_8bit_t *lcd);
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, u8 command);
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd, u8 data);
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd,u8 row, u8 column, u8 data);
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd, u8 *str);
Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd, u8 row, u8 column, u8 *str);
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, u8 row, u8 column, 
                                         const u8 _chr[], u8 mem_pos);

Std_ReturnType convert_uint8_to_string(u8 value, u8 *str);
Std_ReturnType convert_uint16_to_string(u16 value, u8 *str);
Std_ReturnType convert_uint32_to_string(u32 value, u8 *str);


#endif	/* HAL_CLCD_H */

