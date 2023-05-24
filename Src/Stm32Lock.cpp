//
// Created by kosmx on 2023-05-24.
//

#include "Stm32Lock.h"

Stm32Lock::Stm32Lock(LockingData_t *lock) {
    lockingData = lock;
    stm32_lock_acquire(lock);
}

Stm32Lock::~Stm32Lock() {
    stm32_lock_release(lockingData);
}
