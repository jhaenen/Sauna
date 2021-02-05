#ifndef DT_H_
#define DT_H_

#include <stdint.h>

struct HVColor {
    uint8_t h = 0;
    uint8_t v = 255;

    bool operator==(const HVColor& b) { return this->h == b.h && this->v == b.v; }
    bool operator!=(const HVColor& b) { return this->h != b.h || this->v != b.v; }
};

#endif