/**
 * @file bsp_delay.h
 * @brief This file contains all the function prototypes for
 *        the bsp_delay.c file
 */

#ifndef __BSP_DELAY_H
#define __BSP_DELAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "bsp.h"

void DWT_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_DELAY_H */
