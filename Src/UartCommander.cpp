//
// Created by kosmx on 2023-05-24.
//

#include <string>
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

void UART_send_string(std::string str) {
    HAL_UART_Transmit(&huart2, reinterpret_cast<const uint8_t *>(str.data()), str.size(), 1000);
}

/** This function will be invoked to interpret data
 * Calling next_byte() will wait non-blocking until byte is received
 */
void UartCommander::readStream() {
    char nextCommand = next_byte();
    switch (nextCommand) {
        case 'g':
            UART_send_string("Command parser operational :D\n");
            break;
        case 'p': // programming
            readStream();
            break;
    }
}

void UartCommander::readProgram() {

}

