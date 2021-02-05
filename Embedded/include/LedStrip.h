#ifndef LED_STRIP_H_
#define LED_STRIP_H_

#include <stdint.h>

#include "FastLED_RGBW.h"
#include "dt.h"

#ifndef DATA_PIN
    #define DATA_PIN 12
#endif

class LedStrip {
private:
    CRGBW* leds;
    uint16_t numLeds;

    HVColor target;
    HVColor current;

    bool onOff = true;
    bool whiteMode = false;
    uint8_t whiteTarget = 128;
    uint8_t whiteCurrent = 100;
public:
    void setHV(uint8_t h, uint8_t v);
    void setWhite(uint8_t bri);

    void setTarget(uint8_t h, uint8_t v);
    void followTarget();
    HVColor getTarget();

    void turnOnOff(bool onOff);
    void setWhiteMode(bool onOff);

    LedStrip(uint16_t numLeds);
    ~LedStrip();
};

#endif