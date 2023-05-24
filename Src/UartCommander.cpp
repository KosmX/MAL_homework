//
// Created by kosmx on 2023-05-24.
//

#include "UartCommander.h"
#include "usart.h"

UartCommand *UartCommander::newData(uint8_t byte) {
    auto cmd = reinterpret_cast<UartCommand*>(readerThread.call(reinterpret_cast<void*>(byte))); // This call sends data and maybe receive something useful
    return cmd;
}


void UartCommander::init() {
    readerThread.start([this](ProtoThreadWrapper<4096>* ctx) -> void *{
        while (true) { // yes, i know about the endless loop, it won't be an issue
            this->readStream();
        }
    });
}

uint8_t UartCommander::next_byte() {
    return reinterpret_cast<std::uintptr_t>(readerThread.suspend(nullptr));
}

void UartCommander::readStream() {
    uint8_t d[3];
    d[0] = next_byte();
    d[1] = next_byte();
    d[2] = '\n';
    HAL_UART_Transmit(&huart2, d, 3, HAL_MAX_DELAY);
}

