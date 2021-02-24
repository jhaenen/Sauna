#pragma once

#include <stdint.h>

#include "FastLED_RGBW.h"
#include "dt.h"

#ifndef DATA_PIN
    #define DATA_PIN D8
#endif

class LedStrip {
private:
    CRGBW* leds;
    uint16_t numLeds;

    HVColor target;
    HVColor current;

    bool onOff = true;
    bool whiteMode = false;
public:
    void setHV(uint8_t h, uint8_t v);
    void setWhite(uint8_t bri);

    void setTarget(uint8_t h, uint8_t v, uint8_t w);
    void followTarget();
    HVColor getTarget();

    void turnOnOff(bool onOff);
    void toggleOnOff() { turnOnOff(!onOff); };
    bool getOnOff() { return onOff; }

    void setWhiteMode(bool onOff);
    void toggleWhiteMode() { setWhiteMode(!whiteMode); }

    LedStrip(uint16_t numLeds);
    ~LedStrip();
};