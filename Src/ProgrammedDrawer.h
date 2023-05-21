//
// Created by kosmx on 2023-05-21.
//

#ifndef MAL_HOMEWORK_PROGRAMMEDDRAWER_H
#define MAL_HOMEWORK_PROGRAMMEDDRAWER_H

#include "IDrawer.h"

class ProgrammedDrawer : IDrawer {
public:
    std::vector<std::pair<float, std::vector<LED>>> data;

    void setLEDs(float location, std::vector<LED> &leds) override;
    // TODO create constructor from binary data
};

#endif //MAL_HOMEWORK_PROGRAMMEDDRAWER_H
