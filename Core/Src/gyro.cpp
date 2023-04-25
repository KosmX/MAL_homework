//
// Created by kosmx on 2023-04-25.
//

#include "gyro.h"
#include "main.h"
#include "i2c.h"

const char WHO_AM_I = 0x0F;
const char CTRL_REG1 = 0x20;

const char DATACAPTURE = 0x25;
const char OUT_TEMP = 0x26;
const char STATUS_REG = 0x27;
const char OUT_DAT = 0x28;
const char FIFO_CTRL_REG = 0x2E;
const char FIFO_SRC_REG = 0x2F;


bool init_gyro() {

    // if set to high, IMU uses IIC
    HAL_GPIO_WritePin(GYRO_CS_GPIO_Port, GYRO_CS_Pin, GPIO_PinState::GPIO_PIN_SET);
    HAL_Delay(10);

    {
        unsigned char whoami = 0;
        HAL_I2C_Mem_Read(&hi2c1, GYRO_ADDR, WHO_AM_I, 1, &whoami, 1, 10);
        return whoami == 0b11010100;
    }
}
