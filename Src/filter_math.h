//
// Created by kosmx on 2023.05.17..
//

#ifndef MAL_HOMEWORK_FILTER_MATH_H
#define MAL_HOMEWORK_FILTER_MATH_H

// c++ code guard
#ifdef __cplusplus

// STM32F4 has FPU, I don't need to do fixed-point arithmetic :D


class LPF {
public:
    float alpha = 0.01;
    float y = 0;
    float sample(float x);

    inline float operator() (float x) {
        return sample(x);
    }
};

class HPF {
public:
    float alpha = 0.01;
    float y = 0;
    float sample(float x);

    inline float operator() (float x) {
        return sample(x);
    }

private:
    float x_1 = 0;
};

#endif

#endif //MAL_HOMEWORK_FILTER_MATH_H
