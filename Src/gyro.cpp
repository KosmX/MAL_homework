//
// Created by kosmx on 2023-04-25.
//

#include "gyro.h"
#include "main.h"
#include "i2c.h"

const char WHO_AM_I = 0x0F;
const char CTRL_REG = 0x1F;

const char DATACAPTURE = 0x25;
const char OUT_TEMP = 0x26;
const char STATUS_REG = 0x27;
const char OUT_DAT = 0x28;
const char FIFO_CTRL_REG = 0x2E;
const char FIFO_SRC_REG = 0x2F;

int16_t static_error[3] = {260, -325, -60};


bool init_gyro() {

    // if set to high, IMU uses IIC
    HAL_GPIO_WritePin(GYRO_CS_GPIO_Port, GYRO_CS_Pin, GPIO_PinState::GPIO_PIN_SET);
    HAL_Delay(10);

    unsigned char whoami = 0;
    {
        //HAL_I2C_(&hi2c1, GYRO_ADDR, WHO_AM_I, 1, &whoami, 1, 10);
        HAL_I2C_Mem_Read(&hi2c1, GYRO_ADDR, WHO_AM_I, I2C_MEMADD_SIZE_8BIT, &whoami, 1, 10);

        //HAL_I2C_Mem_Read(&hi2c1, GYRO_ADDR, WHO_AM_I, 1, &whoami, 1, 10);

    }
    auto match = whoami == 0b00110011;

    if (!match) return false; // device init failed

    {
        uint8_t initReg1 = 0b01110111;// 400 Hz, xyz en
        HAL_I2C_Mem_Write(&hi2c1, GYRO_ADDR, CTRL_REG + 1, I2C_MEMADD_SIZE_8BIT, &initReg1, 1, 10);

        uint8_t initReg4 = 0b10111000;// Block update, 16g, HR
        HAL_I2C_Mem_Write(&hi2c1, GYRO_ADDR, CTRL_REG + 2, I2C_MEMADD_SIZE_8BIT, &initReg4, 1, 10);


    }
    {
        int16_t _[3];
        //read_gyro(_); // read data to reset drdy pin
    }
    return true;
}

bool read_gyro(int16_t *pData) {

    uint8_t tmp[6] = {0};
    auto data = reinterpret_cast<uint16_t*>(pData);
    if (HAL_I2C_Mem_Read(&hi2c1, GYRO_ADDR, OUT_DAT | 0x80, I2C_MEMADD_SIZE_8BIT, tmp, 6, 10) != HAL_OK) return false;
    data[0] = ((tmp[1] << 8) | tmp[0]);
    data[1] = ((tmp[3] << 8) | tmp[2]);
    data[2] = ((tmp[5] << 8) | tmp[4]);

    //data[0] -= static_error[0];
    //data[1] -= static_error[1];
    //data[2] -= static_error[2];
    pData[0] = pData[0] >> 4; // hopefully it will work...
    pData[1] = pData[1] >> 4;
    pData[2] = pData[2] >> 4;

    return true;
}

