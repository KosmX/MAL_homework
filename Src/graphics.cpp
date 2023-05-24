//
// Created by kosmx on 2023-05-21.
//

#include <algorithm>
#include <vector>
#include <cmath>
#include "graphics.h"
#include "IDrawer.h"
#include "shr.h"


Graphics::Graphics() {
    inputHPF.alpha = 0.9845349610; // ~ 0.5Hz
    //inputLPF.alpha = .5; // very small (
}

// prints from 0 to 48
void printAbs(float u, led_array& leds) {
    int x = static_cast<int>(std::abs(u));

    for(auto& led : leds) {
        led = {}; // now LED has a default (turned off) constructor
    }

    for (int i = 0; i < std::min(x, 16); i++) {
        leds[i].r = true;
    }
    for (int i = 0; i < std::min(x - 16, 16); i++) {
        leds[i].g = true;
    }
    for (int i = 0; i < std::min(x - 32, 16); i++) {
        leds[i].b = true;
    }
}

void Graphics::update(float acceleration, led_array& leds) {
    auto x = inputHPF(acceleration);

    // ----- CONTROL LOGIC -----
    // positive zero crossing
    if (x_1 < 0 && x >= 0 || tickSinceZero > 200) { // min frequency is 1Hz
        enabled = (sensorDataToG(xMax - xMin) > 2); // requires total of 2g acceleration difference to start. (avoid nonsense blinking)
        xMax = 0;
        xMin = 0;

        angularFrequency = 2 * M_PI/(tickSinceZero);
        tickSinceZero = 0;
    }

    if (x > xMax) xMax = x;
    if (x < xMin) xMin = x;

    // ----- GRAPHICS LOGIC -----
    if (enabled && drawLogic != nullptr) {
        // here goes the fancy draw function+

        // position between 1 and 0 (top and bottom)
        auto pos = (std::cos(getPhase()) + 1) / 2;

        drawLogic->setLEDs(pos, leds);
    }
    else {
        printAbs(x/2, leds);
    }
    SHR_write(leds.data());


    tickSinceZero++;
    x_1 = x;
}

