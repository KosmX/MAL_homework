//
// Created by kosmx on 2023.05.17..
//

#include "filter_math.h"

float LPF::sample(float x) {

    return y = alpha * x + (1 - alpha) * y;
}

float HPF::sample(float x) {
    TODO();
}
