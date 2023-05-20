//
// Created by kosmx on 2023-04-27.
//

#include "GPIO_manager.h"
#include "gpio.h"

bool GPIO_manager::read() {
    return HAL_GPIO_ReadPin(port, pin) == GPIO_PinState::GPIO_PIN_SET;
}

void GPIO_manager::write(bool state) {
    HAL_GPIO_WritePin(port, pin, state ? GPIO_PinState::GPIO_PIN_SET : GPIO_PinState::GPIO_PIN_RESET);
}

bool GPIO_manager::rising_edge() {
    auto state = read();
    bool r = !last_state && state;
    last_state = state;
    return r;
}

bool GPIO_manager::falling_edge() {
    auto state = read();
    bool r = last_state && !state;
    last_state = state;
    return r;
}
