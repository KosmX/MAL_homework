//
// Created by kosmx on 2023-05-24.
//

#ifndef MAL_HOMEWORK_STM32LOCK_H
#define MAL_HOMEWORK_STM32LOCK_H

#ifdef __cplusplus
#include "stm32_lock.h"

class Stm32Lock {
public:
    Stm32Lock(LockingData_t* lock);

    ~Stm32Lock();
private:
    LockingData_t* lockingData;
};

#endif
#endif //MAL_HOMEWORK_STM32LOCK_H
