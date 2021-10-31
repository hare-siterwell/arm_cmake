/**
 * @file bsp_usart.c
 * @brief Manage USART
 */

#include "bsp_usart.h"

struct UsartRx ur1, ur2, ur3;

/**
 * @brief Enable USART
 * @param USARTx Universal Synchronous Asynchronous Receiver Transmitter
 */
void USART_Enable(USART_TypeDef *USARTx) {
  OS_ERR err;
  if (USARTx == USART1) {
    OSSemCreate(&ur1.sta, "ur1 sta", 0, &err);
    LL_USART_EnableIT_RXNE(USART1);
    LL_USART_EnableIT_IDLE(USART1);
  } else if (USARTx == USART2) {
    OSSemCreate(&ur2.sta, "ur2 sta", 0, &err);
    LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_6,
                            LL_USART_DMA_GetRegAddr(USART2));
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_6, *(u32 *)ur2.buf);
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_6, USART_RXSIZE);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_6);
    LL_USART_EnableDMAReq_RX(USART2);
    LL_USART_EnableIT_IDLE(USART2);

    LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_7,
                            LL_USART_DMA_GetRegAddr(USART2));
    LL_USART_EnableDMAReq_TX(USART2);
  } else if (USARTx == USART3) {
    OSSemCreate(&ur3.sta, "ur3 sta", 0, &err);
    LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_3,
                            LL_USART_DMA_GetRegAddr(USART3));
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_3, *(u32 *)ur3.buf);
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_3, USART_RXSIZE);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_3);
    LL_USART_EnableDMAReq_RX(USART3);
    LL_USART_EnableIT_IDLE(USART3);

    LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_2,
                            LL_USART_DMA_GetRegAddr(USART3));
    LL_USART_EnableDMAReq_TX(USART3);
  }
}

/**
 * @brief USART callbacks
 * @param USARTx Universal Synchronous Asynchronous Receiver Transmitter
 */
void USART_Callback(USART_TypeDef *USARTx) {
  OS_ERR err;
  if (USARTx == USART1) {
    if (LL_USART_IsActiveFlag_IDLE(USART1) || ur1.len >= USART_RXSIZE) {
      LL_USART_ClearFlag_IDLE(USART1);
      LL_USART_DisableDirectionRx(USART1);
      ur1.len ? OSSemPost(&ur1.sta, OS_OPT_POST_1, &err) // Processing data
              : USART_ReEnable(USART1);
    } else if (LL_USART_IsActiveFlag_RXNE(USART1)) {
      ur1.buf[ur1.len++] = LL_USART_ReceiveData8(USART1);
    }
  } else if (USARTx == USART2 && LL_USART_IsActiveFlag_IDLE(USART2)) {
    LL_USART_ClearFlag_IDLE(USART2);
    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_6);
    ur2.len = USART_RXSIZE - LL_DMA_GetDataLength(DMA1, LL_DMA_CHANNEL_6);
    ur2.len ? OSSemPost(&ur2.sta, OS_OPT_POST_1, &err) // Processing data
            : USART_ReEnable(USART2);
  } else if (USARTx == USART3 && LL_USART_IsActiveFlag_IDLE(USART3)) {
    LL_USART_ClearFlag_IDLE(USART3);
    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_3);
    ur3.len = USART_RXSIZE - LL_DMA_GetDataLength(DMA1, LL_DMA_CHANNEL_3);
    ur3.len ? OSSemPost(&ur3.sta, OS_OPT_POST_1, &err) // Processing data
            : USART_ReEnable(USART3);
  }
}

/**
 * @brief Re-enable DMA mode for reception
 * @param USARTx Universal Synchronous Asynchronous Receiver Transmitter
 */
void USART_ReEnable(USART_TypeDef *USARTx) {
  if (USARTx == USART1) {
    memset(ur1.buf, 0, ur1.len);
    ur1.len = 0;
    LL_USART_EnableDirectionRx(USART1);
  } else if (USARTx == USART2) {
    memset(ur2.buf, 0, ur2.len);
    ur2.len = 0;
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_6, USART_RXSIZE);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_6);
  } else if (USARTx == USART3) {
    memset(ur3.buf, 0, ur3.len);
    ur3.len = 0;
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_3, USART_RXSIZE);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_3);
  }
}

/**
 * @brief Sends an amount of data in DMA mode
 * @param USARTx Universal Synchronous Asynchronous Receiver Transmitter
 * @param pData Pointer to data buffer
 * @param Size Amount of data elements
 */
void USART_Send(USART_TypeDef *USARTx, u8 *pData, u32 Size) {
  if (USARTx == USART2) {
    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_7);
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_7, *(u32 *)pData);
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_7, Size);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_7);
  } else if (USARTx == USART3) {
    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_2, *(u32 *)pData);
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, Size);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);
  }
}

/* Support "printf()" */
#ifdef __GNUC__
int _write(int fd, char *pBuffer, int size) {
  for (u32 i = 0; i < size; i++) {
    while (!LL_USART_IsActiveFlag_TXE(USART1))
      ;
    LL_USART_TransmitData8(USART1, pBuffer[i]);
  }
  return size;
}
#else
FILE __stdout;
void _sys_exit(int x) {}
int fputc(int ch, FILE *f) {
  LL_USART_TransmitData8(USART1, ch);
  while (!LL_USART_IsActiveFlag_TXE(USART1))
    ;
  return ch;
}
#endif
