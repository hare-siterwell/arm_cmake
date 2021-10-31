/**
 * @file task_usart.c
 * @brief Application task body
 */

#include "bsp_usart.h"

/**
 * @brief USART1 communication with PC
 */
void task_usart1(void *p_arg) {
  OS_ERR err;
  USART_Enable(USART1);
  printf("Task USART1 Running!\r\n");
  while (1) {
    OSSemPend(&ur1.sta, 0, OS_OPT_PEND_BLOCKING, 0, &err);

    printf("%s\r\n", ur1.buf);

    USART_ReEnable(USART1);
  }
}
