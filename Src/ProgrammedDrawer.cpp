//
// Created by kosmx on 2023-05-21.
//

#include "ProgrammedDrawer.h"

void ProgrammedDrawer::setLEDs(float location, std::vector<LED> &leds) {
    //search in the data array
    int i = 0;
    while (data[i].first > location && data.size() > i + 1) {i++;}

    // set the array
    auto& entry = data[i].second;

    for (i = 0; i < leds.size(); i++) {
        leds[i] = entry[i];
    }
}
