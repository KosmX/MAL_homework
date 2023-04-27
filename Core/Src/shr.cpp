//
// Created by kosmx on 2023-04-21.
//

#include "shr.h"
#include "spi.h"
#include "main.h"

SHR_data staticWriteData{};

void init_shift_register() {

    HAL_GPIO_WritePin(SHR_LE_GPIO_Port, SHR_LE_Pin, GPIO_PinState::GPIO_PIN_SET);

}

void SHR_write(uint8_t *data) {
    HAL_GPIO_WritePin(SHR_LE_GPIO_Port, SHR_LE_Pin, GPIO_PinState::GPIO_PIN_RESET);
    HAL_SPI_Transmit_DMA(&hspi3, data, 6);
}

void SHR_write(SHR_data& data) {
    if (&data != &staticWriteData) {
        staticWriteData = data;
    }
    SHR_write(staticWriteData.data);
}

void SHR_write(LED *leds) {
    staticWriteData.setLEDs(leds);
    SHR_write(staticWriteData);
}


extern "C" void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi) {
    if (hspi == &hspi3) {
        HAL_GPIO_WritePin(SHR_LE_GPIO_Port, SHR_LE_Pin, GPIO_PinState::GPIO_PIN_SET);
    }
}

void SHR_data::setLEDs(LED *values) {
    {
        for (unsigned char & i : data) {
            i = 0;
        }

        int bit = 0;
        int pos = 5;

        for(int i = 0; i < 16; i++) {
            for (int c = 2; c >= 0; c--) {

                bool color;
                switch (c) {
                    case 0:
                        color = values[15 - i].r;
                        break;
                    case 1:
                        color = values[15 - i].g;
                        break;
                    case 2:
                        color = values[15 - i].b;
                        break;
                }
                /*
                if (color) {
                    color = true;
                } else {
                    color = false;
                }*/

                data[pos] |= (color) << bit;


                if (bit == 7) {
                    pos--;
                    bit = 0;
                } else {
                    bit++;
                }
            }
        }
    }
}
