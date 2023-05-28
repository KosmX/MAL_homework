//
// Created by kosmx on 2023-05-24.
//

#ifndef MAL_HOMEWORK_UART_ASYNC_H
#define MAL_HOMEWORK_UART_ASYNC_H

#include <cstdint>

#ifdef __cplusplus
#include "Stm32Lock.h"


/**
 * Class implementing UART receiving using DMA ringbuffer mode.
 * it makes no interrupt, and because the index read is atomic, it is safe
 *
 * The class is not thread-safe, reading from multiple threads may cause problems. Writing and reading is safe :D
 */
class AsyncUartReceiver {
public:

    void init();
    [[nodiscard]] bool isNotEmpty() const;

    uint16_t read();

    void callback();
    const static int data_size = 128;
private:
    uint8_t byte = 0;
    volatile uint8_t uart_data[data_size] = {0};
    int uart_pos = 0;
    LockingData_t lock = LOCKING_DATA_INIT;
};


extern AsyncUartReceiver AsyncUartInstance;

#endif
#endif //MAL_HOMEWORK_UART_ASYNC_H
