//
// Created by kosmx on 2023-05-27.
//

#include "Packets.h"
#include "usart.h"

void StringMsg::write() {
    uint8_t c = 's';
    HAL_UART_Transmit(&huart2, &c, 1, 100);
    HAL_UART_Transmit(&huart2, reinterpret_cast<const uint8_t *>(str.c_str()), str.size() + 1, 1000);
}

void FreqPacket::write() {
    uint8_t data[5];
    data[0] = 'f';
    auto* fp = reinterpret_cast<uint32_t*>(&freq); // take it as int
    data[2] = (*fp >> 0) & 0xff;
    data[2] = (*fp >> 8) & 0xff;
    data[2] = (*fp >> 16) & 0xff;
    data[2] = (*fp >> 24) & 0xff;
    HAL_UART_Transmit(&huart2, data, 5, 1000);
}
