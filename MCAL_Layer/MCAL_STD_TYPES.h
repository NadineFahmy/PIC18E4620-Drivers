/* 
 * File:   MCAL_STD_TYPES.h
 * Author: Nadine
 *
 * Created on November 19, 2023, 1:56 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/* Section : Include */
#include "COMPILER.h"
#include "STD_LIBs.h"

/*Section : Macro Function Declaration */

/*Section : Datatype Declaration */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

typedef u8 Std_ReturnType;

/*Section : Macro Declaration */
#define STD_HIGH            0x01
#define STD_LOW             0x00

#define STD_ON              0x01
#define STD_OFF             0x00

#define STD_ACTIVE          0X01
#define STD_IDLE            0x00

#define E_OK                (Std_ReturnType) 0x01
#define E_NOT_OK            (Std_ReturnType) 0x00

#endif	/* MCAL_STD_TYPES_H */

