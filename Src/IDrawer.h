//
// Created by kosmx on 2023-05-21.
//

#ifndef MAL_HOMEWORK_IDRAWER_H
#define MAL_HOMEWORK_IDRAWER_H

#include <array>
#include "shr.h"

typedef std::array<LED, 16> led_array;

class IDrawer {
public:
    /**
     * Draw something
     * @param location toy location between 1 and 0
     * @param leds array of LEDs (will be written by invoker)
     */
     // LED array is 2.6666666667 times more data than SHR_data, but it way easier to handle.
     // my program isn't memory limited (128K ram MCU), so having garbage data is okay..
    virtual void setLEDs(float location, led_array& leds) = 0;
};

#endif //MAL_HOMEWORK_IDRAWER_H
