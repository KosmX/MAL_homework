//
// Created by kosmx on 2023-05-24.
//


#include "Uart_async.h"
#include "usart.h"
#include "dma.h"

inline int getUartDptr() {
    return AsyncUartReceiver::data_size - huart2.hdmarx->Instance->NDTR;
}

AsyncUartReceiver AsyncUartInstance{};

void AsyncUartReceiver::init() {
    HAL_UART_Receive_DMA(&huart2, const_cast<uint8_t *>(uart_data), data_size);
}

bool AsyncUartReceiver::isNotEmpty() const {
    return getUartDptr() != uart_pos;
}

// up-to 1 word (int) read/writes are atomic (source: ARM M4 docs)
uint16_t AsyncUartReceiver::read() {

    if (getUartDptr() == uart_pos) return -1;


    auto r = uart_data[uart_pos++];
    if (uart_pos >= data_size) uart_pos = 0;

    return r;
}
