//
// Created by kosmx on 2023-04-25.
//

// Acceleration measure (acc may refer to accumulator)
#ifndef MAL_HOMEWORK_ACCMU_H
#define MAL_HOMEWORK_ACCMU_H
#include "main.h"

const char GYRO_ADDR = (0b0011000 | 1) << 1;

bool init_accmu();


bool read_accmu(int16_t *data);


#endif //MAL_HOMEWORK_ACCMU_H
