/**
 * @file app_main.c
 * @brief Application main task body
 */

#include "bsp_delay.h"
#include "bsp_usart.h"

static OS_TCB Task1TCB;
static CPU_STK Task1Stk[512];
static OS_TCB Task2TCB;
static CPU_STK Task2Stk[512];

void task_usart1(void *p_arg);
void task_led(void *p_arg);

/**
 * @brief The application main task
 */
void app_main(void *p_arg) {
  OS_ERR err;
  DWT_Init();

#if OS_CFG_SCHED_ROUND_ROBIN_EN
  OSSchedRoundRobinCfg(DEF_ENABLED, 0, &err);
#endif

  OSTaskCreate(&Task1TCB, "Task1", task_usart1, 0, 5, Task1Stk, 512 / 10, 512,
               0, 0, 0, OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR, &err);
  OSTaskCreate(&Task2TCB, "Task2", task_led, 0, 5, Task2Stk, 512 / 10, 512, 0,
               0, 0, OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR, &err);
}
