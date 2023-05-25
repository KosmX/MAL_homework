//
// Created by kosmx on 2023-05-24.
//

#ifndef MAL_HOMEWORK_UARTCOMMANDER_H
#define MAL_HOMEWORK_UARTCOMMANDER_H


#include <cstdint>
#include "ProtoThreadWrapper.h"
#include "IDrawer.h"

class UartCommand {
public:
    virtual void execute() = 0;
};

class SimpleCommand : UartCommand {

};

/**
 * Receive and process UART data
 */
class UartCommander {
public:

    void init();

    /**
     * new data received, interpret it
     * @param byte byte
     * @return Command to execute or nullptr if not yet full
     */
    IDrawer* newData(uint8_t byte);
private:
    ProtoThreadWrapper<4096> readerThread {}; /* this is nothing :D */

    void readStream();

    /**
     * Non-blocking read next byte (the scheduler is hidden somewhere else ;)
     * @return byte from UART
     */
    uint8_t next_byte();

    void readProgram();
    void* sendStuff = nullptr;
};


#endif //MAL_HOMEWORK_UARTCOMMANDER_H
