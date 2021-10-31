/**
 * @file bsp_led.h
 * @brief This file contains all the function prototypes for
 *        the bsp_led.c file
 */

#ifndef __BSP_LED_H
#define __BSP_LED_H

#ifdef __cplusplus
extern "C" {
#endif

#include "bsp.h"

#define LED_R(n)                                                               \
  n ? LL_GPIO_SetOutputPin(RED_GPIO_Port, RED_Pin)                             \
    : LL_GPIO_ResetOutputPin(RED_GPIO_Port, RED_Pin)

#define LED_G(n)                                                               \
  n ? LL_GPIO_SetOutputPin(GREEN_GPIO_Port, GREEN_Pin)                         \
    : LL_GPIO_ResetOutputPin(GREEN_GPIO_Port, GREEN_Pin)

#define LED_B(n)                                                               \
  n ? LL_GPIO_SetOutputPin(BLUE_GPIO_Port, BLUE_Pin)                           \
    : LL_GPIO_ResetOutputPin(BLUE_GPIO_Port, BLUE_Pin)

#ifdef __cplusplus
}
#endif

#endif /* __BSP_LED_H */
