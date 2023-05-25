//
// Created by kosmx on 2023-05-24.
//

#include <string>
#include "UartCommander.h"
#include "usart.h"
#include "IDrawer.h"
#include "ProgrammedDrawer.h"

IDrawer *UartCommander::newData(uint8_t byte) {
    auto cmd = reinterpret_cast<IDrawer*>(readerThread.call(reinterpret_cast<void*>(byte))); // This call sends data and maybe receive something useful
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
    auto b = reinterpret_cast<std::uintptr_t>(readerThread.suspend(sendStuff));
    sendStuff = nullptr;
    return b;
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
            readProgram();
            break;
    }
}

void UartCommander::readProgram() {

    uint8_t data_size = next_byte();
    std::vector<std::pair<float, led_array>> data {data_size};
    for (int i = 0; i < data_size; i++) {
        uint32_t fl = 0;
        fl |= next_byte();
        fl |= next_byte() << 8;
        fl |= next_byte() << 16;
        fl |= next_byte() << 24;
        data[i].first = *reinterpret_cast<float*>(&fl);
        for(auto& led : data[i].second) {
            led = next_byte();
        }
    }
    // this will be sent to another thread
    sendStuff = new ProgrammedDrawer(std::move(data));

}

