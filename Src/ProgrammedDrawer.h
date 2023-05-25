//
// Created by kosmx on 2023-05-21.
//

#ifndef MAL_HOMEWORK_PROGRAMMEDDRAWER_H
#define MAL_HOMEWORK_PROGRAMMEDDRAWER_H

#include <vector>
#include "IDrawer.h"

class ProgrammedDrawer : IDrawer {
public:
    std::vector<std::pair<float, led_array>> data;

    void setLEDs(float location, led_array &leds) override;
    // TODO create constructor from binary data

    // forwarding vector, avoid unnecessary allocations
    explicit ProgrammedDrawer(std::vector<std::pair<float, led_array>>&& data): data{ std::move(data) } {};

    ~ProgrammedDrawer() override = default;
};

#endif //MAL_HOMEWORK_PROGRAMMEDDRAWER_H
