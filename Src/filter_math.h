//
// Created by kosmx on 2023.05.17..
//

#ifndef MAL_HOMEWORK_FILTER_MATH_H
#define MAL_HOMEWORK_FILTER_MATH_H

// c++ code guard
#ifdef __cplusplus


class LPF {
public:
    float alpha = 0.01;
    float y = 0;
    float sample(float x);
};

class HPF {
    float alpha = 0.01;
    float y = 0;
    float sample(float x);
private:
    float x_1 = 0;
};

#endif

#endif //MAL_HOMEWORK_FILTER_MATH_H
