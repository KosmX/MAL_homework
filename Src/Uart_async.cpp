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
    return uart_idx != uart_pos;
}

// up-to 1 word (int) read/writes are atomic (source: ARM M4 docs)
uint16_t AsyncUartReceiver::read() {

    if (uart_idx == uart_pos) return -1;


    auto r = uart_data[uart_pos++];
    if (uart_pos >= 128) uart_pos = 0;

    return r;
}

void AsyncUartReceiver::callback() {

    uart_data[uart_idx] = byte; // is locked
    if (++uart_idx >= 128) {
        uart_idx = 0;
    }


    HAL_UART_Receive_IT(&huart2, &AsyncUartInstance.byte, 1);
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2) { // Current UART
        AsyncUartInstance.callback();
    }

}

