//
// Created by kosmx on 2023-04-27.
//

#ifndef MAL_HOMEWORK_GPIO_MANAGER_H
#define MAL_HOMEWORK_GPIO_MANAGER_H

#ifdef __cplusplus
#include <cstdint>
#include "stm32f446xx.h"

/**
 * Simple wrapper for GPIO pins :D
 */
class GPIO_manager {
private:
    GPIO_TypeDef *const port;
    const uint16_t pin;
    bool last_state;
public:
    GPIO_manager(GPIO_TypeDef *p, uint16_t pin, bool initState = false): port{p}, pin{pin}, last_state{initState} {

    }

    /**
     * @return false if pin is LOW, true if pin is HIGH
     */
    bool read();

    /**
     * @param false for LOW, true for HIGH
     */
    void write(bool);

    bool rising_edge();

    bool falling_edge();
};

#endif
#endif //MAL_HOMEWORK_GPIO_MANAGER_H
