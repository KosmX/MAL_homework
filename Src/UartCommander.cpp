//
// Created by kosmx on 2023-05-24.
//

#include <string>
#include "UartCommander.h"
#include "usart.h"
#include "IDrawer.h"
#include "ProgrammedDrawer.h"
#include "Packets.h"
#include "graphics.h"


extern Graphics drawer;

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

void UART_sendPacket(UartPacket& p) {
    p.write();
}


/** This function will be invoked to interpret data
 * Calling next_byte() will wait non-blocking until byte is received
 */
void UartCommander::readStream() {
    char nextCommand = next_byte();
    switch (nextCommand) {
        case 'g':
            StringMsg("Command parser operational :D\n").write(true);
            break;
        case 'p': // programming
            readProgram();
            break;
        case 'f':
            FreqPacket(drawer.getFrequency()).write();
            break;
        case 'l':
            StringMsg::debug = !StringMsg::debug;
            StringMsg(std::string{"Logging "} + (StringMsg::debug ? "enabled" : "disabled")).write(true);
            break;
        case 't':
            StringMsg("pong").write(true);
            break;
        default:
            StringMsg("error, unknown command: " + (std::to_string(nextCommand))).write(true);
    }
}

void UartCommander::readProgram() {

    //StringMsg("Start receiving program").write();

    uint8_t data_size = next_byte();
    std::vector<std::pair<float, led_array>> data {data_size};
    StringMsg("reading " + std::to_string(data_size) + " rows").write();
    for (int i = 0; i < data_size; i++) {
        uint32_t fl = 0;
        fl |= next_byte();
        fl |= next_byte() << 8;
        fl |= next_byte() << 16;
        fl |= next_byte() << 24;
        data[i].first = *reinterpret_cast<float*>(&fl);

        StringMsg("line " + std::to_string(i) + " position: " + std::to_string(data[i].first)).write();
        for(auto& led : data[i].second) {
            led = LED{next_byte()};
        }
    }
    // this will be sent to another thread
    if (data_size > 0) {
        StringMsg("program updated").write(true);
        sendStuff = new ProgrammedDrawer(std::move(data));
    }
}
