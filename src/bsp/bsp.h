/**
 * @file bsp.h
 * @brief Defines
 */

#ifndef __BSP_H
#define __BSP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "os.h"

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define commonly used data type short keywords */
enum bool { FALSE, TRUE };

typedef signed int s32;
typedef signed short s16;
typedef signed char s8;

typedef const signed int sc32;
typedef const signed short sc16;
typedef const signed char sc8;

typedef volatile signed int vs32;
typedef volatile signed short vs16;
typedef volatile signed char vs8;

typedef volatile const signed int vsc32;
typedef volatile const signed short vsc16;
typedef volatile const signed char vsc8;

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef const unsigned int uc32;
typedef const unsigned short uc16;
typedef const unsigned char uc8;

typedef volatile unsigned int vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char vu8;

typedef volatile const unsigned int vuc32;
typedef volatile const unsigned short vuc16;
typedef volatile const unsigned char vuc8;

void delay_us(u32 nus);
void delay_ms(u32 nms);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_H */
