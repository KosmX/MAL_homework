//
// Created by kosmx on 2023-04-21.
//

#ifndef MAL_HOMEWORK_SHR_H
#define MAL_HOMEWORK_SHR_H



#ifdef __cplusplus
extern "C" {
#include <cstdint>
#else
#include<stdbool.h>
#endif

    void init_shift_register();

//void SHR_write(uint8_t *data[6]); // this is internal stuff

struct LED {
    bool r: 1;
    bool g: 1;
    bool b: 1;
};


#ifdef __cplusplus
}

union SHR_data {
public:
    struct {
        bool LED15_R: 1 = false;
        bool LED15_G: 1 = false;
        bool LED15_B: 1 = false;
        bool LED14_R: 1 = false;
        bool LED14_G: 1 = false;
        bool LED14_B: 1 = false;
        bool LED13_R: 1 = false;
        bool LED13_G: 1 = false;
        bool LED13_B: 1 = false;
        bool LED12_R: 1 = false;
        bool LED12_G: 1 = false;
        bool LED12_B: 1 = false;
        bool LED11_R: 1 = false;
        bool LED11_G: 1 = false;
        bool LED11_B: 1 = false;
        bool LED10_R: 1 = false;
        bool LED10_G: 1 = false;
        bool LED10_B: 1 = false;
        bool LED9_R: 1 = false;
        bool LED9_G: 1 = false;
        bool LED9_B: 1 = false;
        bool LED8_R: 1 = false;
        bool LED8_G: 1 = false;
        bool LED8_B: 1 = false;
        bool LED7_R: 1 = false;
        bool LED7_G: 1 = false;
        bool LED7_B: 1 = false;
        bool LED6_R: 1 = false;
        bool LED6_G: 1 = false;
        bool LED6_B: 1 = false;
        bool LED5_R: 1 = false;
        bool LED5_G: 1 = false;
        bool LED5_B: 1 = false;
        bool LED4_R: 1 = false;
        bool LED4_G: 1 = false;
        bool LED4_B: 1 = false;
        bool LED3_R: 1 = false;
        bool LED3_G: 1 = false;
        bool LED3_B: 1 = false;
        bool LED2_R: 1 = false;
        bool LED2_G: 1 = false;
        bool LED2_B: 1 = false;
        bool LED1_R: 1 = false;
        bool LED1_G: 1 = false;
        bool LED1_B: 1 = false;
        bool LED0_R: 1 = false;
        bool LED0_G: 1 = false;
        bool LED0_B: 1 = false;
    } LEDs;
    uint8_t data[6];


    void setLEDs(LED *values);
};
static_assert(sizeof(SHR_data) == 6, "SHR data must be 48 bits or 6 bytes");


void SHR_write(SHR_data& data);

void SHR_write(LED *leds);

#endif


#endif //MAL_HOMEWORK_SHR_H
