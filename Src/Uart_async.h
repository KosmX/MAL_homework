//
// Created by kosmx on 2023-05-24.
//

#ifndef MAL_HOMEWORK_UART_ASYNC_H
#define MAL_HOMEWORK_UART_ASYNC_H

#include <cstdint>

#ifdef __cplusplus
#include "Stm32Lock.h"


class AsyncUartReceiver {
public:

    void init();
    [[nodiscard]] bool isNotEmpty() const;

    uint16_t read();

    void callback();
private:
    uint8_t byte = 0;
    volatile uint8_t uart_data[128] = {0};
    int uart_idx = 0;
    int uart_pos = 0;
    LockingData_t lock = LOCKING_DATA_INIT;
};


extern AsyncUartReceiver AsyncUartInstance;

#endif
#endif //MAL_HOMEWORK_UART_ASYNC_H
