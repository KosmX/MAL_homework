//
// Created by kosmx on 2023-04-21.
//

#include <cmath>
#include "program.h"
#include "main.h"
#include "shr.h"
#include "gyro.h"
#include "tim.h"
#include "GPIO_manager.h"

GPIO_manager button{B1_GPIO_Port, B1_Pin, true};


LED leds[16] = {};
int idx = 0;

volatile bool it = false;
int16_t gyro_data[3] = {0};

void init() {
    // reset LED states. (call the DMA)
    SHR_write(leds);
    init_gyro();

    TIM3->CCR3 = 250;
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
}

void loop() {
    //HAL_Delay(100); // busy-wait 100 ms
    if (it && HAL_GPIO_ReadPin(SHR_LE_GPIO_Port, SHR_LE_Pin) == GPIO_PinState::GPIO_PIN_SET) {
        /*
        leds[idx].r = !leds[idx].r;
        leds[15 - idx].b = !leds[15 - idx].b;

        SHR_write(leds);

        idx++;
        if (idx == 16) {
            idx = 0;
        }//*/
        int len = static_cast<int>(sqrt(gyro_data[0] * gyro_data[0] + gyro_data[1] * gyro_data[1] + gyro_data[2] * gyro_data[2]) / 512);

        for(auto& led : leds) {
            led = {}; // now LED has a default (turned off) constructor
        }


        for (int i = 0; i < std::min(len, 16); i++) {
            leds[i].r = true;
        }
        for (int i = 0; i < std::min(len - 16, 16); i++) {
            leds[i].g = true;
        }
        for (int i = 0; i < std::min(len - 32, 16); i++) {
            leds[i].b = true;
        }

        SHR_write(leds);
        it = false;
    }

    if (button.falling_edge()) {
        if (TIM3->CCR3 == 250) {
            TIM3->CCR3 = 0;
        } else {
            TIM3->CCR3 = 250;
        }
    }

    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == DRDY_IT_Pin) {
        it = read_gyro(gyro_data);

        /*
        if (it) {
            for (LED &led: leds) {
                led.g = true;
            }
        }
        SHR_write(leds);//*/
    }

}
