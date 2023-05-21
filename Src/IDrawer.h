//
// Created by kosmx on 2023-05-21.
//

#ifndef MAL_HOMEWORK_IDRAWER_H
#define MAL_HOMEWORK_IDRAWER_H

#include <vector>
#include "shr.h"

class IDrawer {
public:
    /**
     * Draw something
     * @param location toy location between 1 and 0
     * @param leds array of LEDs (will be written by invoker)
     */
    virtual void setLEDs(float location, std::vector<LED>& leds) = 0;
};

#endif //MAL_HOMEWORK_IDRAWER_H
