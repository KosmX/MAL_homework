//
// Created by kosmx on 2023-05-21.
//

#ifndef MAL_HOMEWORK_GRAPHICS_H
#define MAL_HOMEWORK_GRAPHICS_H

#include "filter_math.h"
#include "shr.h"

#ifdef __cplusplus
#include "vector"
#include "IDrawer.h"

/**
 * Store and manage position anr rendering stuff. ()
 *
 * acceleration (ideally) will follow a sine-wave
 * I'll detect positive (and optionally negative) zero crossings and peaks to track the current phase and frequency
 *
 */
class Graphics {
public:
    Graphics();

    void update(float acceleration, led_array& leds);

    IDrawer* drawLogic = nullptr;

    float getFrequency() const;

private:
    /**
     * angular frequency of the position (in 1/ticks)
     */
    float angularFrequency = 0;
    // assert angularFrequency < pi; //

    /**
     * Ticks since last positive zero-crossing, this * angularFrequency will give phase
     */
    unsigned int tickSinceZero = 0;

    float getPhase() {
        return tickSinceZero * angularFrequency;
    }

    // helper *static* stuff
    // low-pass filter to filter noise
    //LPF inputLPF{};
    // high-pass filter to filter static acceleration (gravity)
    HPF inputHPF{};

    // last (filtered) signal for detection
    float x_1{};
    float xMax{};
    float xMin{};

    bool enabled = false;

    static inline float sensorDataToG(float data) {
        const float lsb = 0.0082864076; // less-significant bit | value = 24/(2^11) / sqrt(2) | sqrt2 to counteract earlier conversion
        return data * lsb;
    }

};


#endif
#endif //MAL_HOMEWORK_GRAPHICS_H
