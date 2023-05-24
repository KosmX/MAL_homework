//
// Created by kosmx on 2023-05-24.
//


#include "Uart_async.h"
#include "usart.h"


AsyncUartReceiver AsyncUartInstance{};

void AsyncUartReceiver::init() {
    HAL_UART_Receive_IT(&huart2, &byte, 1);
}

bool AsyncUartReceiver::isNotEmpty() const {
    return uart_idx != 0;
}

uint16_t AsyncUartReceiver::read() {
    auto l = Stm32Lock(&lock); // destructor will release the lock :D

    if (uart_idx == 0) return -1;

    auto r = uart_data[0];
    uart_idx--;
    for (int i = 0; i < uart_idx; i++) {
        uart_data[i] = uart_data[i + 1];
    }
    return r;
}

void AsyncUartReceiver::callback() {
    stm32_lock_acquire(&lock);

    if (uart_idx < 64) {
        uart_data[uart_idx++] = byte; // is locked
    }

    stm32_lock_release(&lock);

    HAL_UART_Receive_IT(&huart2, &AsyncUartInstance.byte, 1);
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2) { // Current UART
        AsyncUartInstance.callback();
    }

}

