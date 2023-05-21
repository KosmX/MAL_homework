//
// Created by kosmx on 2023-04-21.
//

#include <cmath>
#include "program.h"
#include "main.h"
#include "shr.h"
#include "accmu.h"
#include "tim.h"
#include "GPIO_manager.h"
#include "graphics.h"

GPIO_manager button{B1_GPIO_Port, B1_Pin, true};


std::vector<LED> leds{16};
int idx = 0;

volatile bool it = false;
int16_t gyro_data[3] = {0};

Graphics drawer{};

void init() {
    // reset LED states. (call the DMA)
    SHR_write(leds.data());

    init_accmu();

    TIM3->CCR3 = 250;
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
    HAL_TIM_Base_Start_IT(&htim2);
}


void loop() {
    //HAL_Delay(100); // busy-wait 100 ms
    if (it && HAL_GPIO_ReadPin(SHR_LE_GPIO_Port, SHR_LE_Pin) == GPIO_PinState::GPIO_PIN_SET) {
        int normal_dir = gyro_data[0] + gyro_data[1]; // positive direction: towards the power supply
        //int len = std::abs(normal_dir/8);
        drawer.update(normal_dir, leds);

        it = false;
    }

    // button brightness control :D
    if (button.falling_edge()) {
        if (TIM3->CCR3 == 250) {
            TIM3->CCR3 = 0;
        } else {
            TIM3->CCR3 = 250; // 2.4% brightness
        }
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
    }


}

void tick() {

    it = read_accmu(gyro_data);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim == &htim2) {
        tick();
    }
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == DRDY_IT_Pin) {
        it = read_accmu(gyro_data);

        /*
        if (it) {
            for (LED &led: leds) {
                led.g = true;
            }
        }
        SHR_write(leds);//*/
    }

}
