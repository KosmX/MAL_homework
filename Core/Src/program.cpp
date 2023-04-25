//
// Created by kosmx on 2023-04-21.
//

#include "program.h"
#include "main.h"
#include "shr.h"
#include "gyro.h"

LED leds[16] = {};
int idx = 0;


void init() {

    if(init_gyro()) {
        for (LED& led : leds) {
            led.g = true;
        }
    }
}

void loop() {
    HAL_Delay(100); // busy-wait 100 ms

    leds[idx].r = !leds[idx].r;
    leds[15 - idx].b = !leds[15 - idx].b;

    SHR_write(leds);

    idx++;
    if (idx == 16) {
        idx = 0;
    }
}

