//
// Created by kosmx on 2023-04-21.
//

#include "program.h"
#include "spi.h"
#include "dma.h"
#include "main.h"
#include "shr.h"

void init() {

}

LED leds[16] = {};
int idx = 0;

void loop() {
    HAL_Delay(100); // busy-wait 100 ms

    leds[idx].r = !leds[idx].r;

    SHR_write(leds);

    idx++;
    if (idx == 16) {
        idx = 0;
    }
}

