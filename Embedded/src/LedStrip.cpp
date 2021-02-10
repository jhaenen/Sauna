#include "LedStrip.h"

LedStrip::LedStrip(uint16_t numLeds) : numLeds(numLeds) {
    leds = new CRGBW[numLeds];
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>((CRGB*)leds, getRGBWsize(numLeds));
}

void LedStrip::setHV(uint8_t h, uint8_t v) {
    for(uint16_t i = 0; i < numLeds; i++) {
        leds[i] = CHSV(h, 255, v);
    }
    FastLED.show();
}

void LedStrip::setWhite(uint8_t bri) {
    if(bri == 0) setHV(0, 0);
    else {
        for(uint16_t i = 0; i < numLeds; i++) {
            leds[i] = CRGBW(0, 0, 0, bri);
        }
        FastLED.show();
    }
}

void LedStrip::setTarget(uint8_t h, uint8_t v, uint8_t a) {
    if(whiteMode) target.w = a;
    else {
        target.h = h;
        target.v = v;
    }
}

void LedStrip::turnOnOff(bool onOff) {
    if(!onOff && this->onOff) { //Turn off
        setHV(0, 0);
        this->onOff = false;
    } else if(onOff && !(this->onOff)) {
        if(whiteMode) setWhite(target.w);
        else setHV(target.h, target.v);
        this->onOff = true;
    }
}

void LedStrip::setWhiteMode(bool onOff) {
    if(!onOff && whiteMode) { //Turn off
        setHV(target.h, target.v);
        whiteMode = false;
    } else if(onOff && !whiteMode) {
        setWhite(target.w);
        whiteMode = true;
    }
}

void LedStrip::followTarget() {
    if(!whiteMode) {
        if(target != current) {
            uint8_t diffH = target.h - current.h;
            if(diffH > 0 && diffH < 128) {
                current.h++;
            } else if(diffH >= 128) {
                current.h--;
            }
            
            int16_t diffV = target.v - current.v;
            if(diffV > 0) {
                current.v++;
            } else if(diffV < 0) {
                current.v--;
            }

            setHV(current.h, current.v);
        }
    } else {
        if(target.w != current.w) {
            int16_t diffV = target.w - current.w;
            if(diffV > 0) {
                current.w++;
            } else if(diffV < 0) {
                current.w--;
            }

            setWhite(current.w);
        }
    }
}

LedStrip::~LedStrip() {
    delete leds;
}
