//
// Created by kosmx on 2023-04-25.
//

#ifndef MAL_HOMEWORK_GYRO_H
#define MAL_HOMEWORK_GYRO_H
#include "main.h"

const char GYRO_ADDR = (0b0011000 | 1) << 1;

bool init_gyro();


bool read_gyro(int16_t *data);


#endif //MAL_HOMEWORK_GYRO_H
