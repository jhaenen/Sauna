#ifndef RGB_CONTROLLER_H_
#define RGB_CONTROLLER_H_

#include <Wire.h>
#include <stdint.h>

#include "dt.h"

#define COLOR_OFFSET 70

enum action_t {
  	BUTTON_ACTION = 128,
  	WIPER_ACTION = 129
};

enum buttonType_t {
	RELEASE_BUTTON    = 0,
	RGB_BUTTON        = 1,
	WHITE_BUTTON      = 2,
	SPEEDUP_BUTTON    = 4,
	SPEEDDOWN_BUTTON  = 8,
	MODE_BUTTON       = 16,
	DIM_BUTTON        = 32,
	ONOFF_BUTTON      = 64
};

enum cdMode_t {
  COLOR_MODE,
  DIM_MODE
};

enum bufferIndex_t {
	ACTION_INDEX = 0,
	BUTTON_INDEX = 1,
	WIPER_INDEX  = 3
};

struct ContEvent {
	uint8_t actionType;
	uint8_t buttonType;
	uint8_t wiperData;

	ContEvent(uint8_t actionType, uint8_t buttonType, uint8_t wiperData) : actionType(actionType), buttonType(buttonType), wiperData(wiperData) {}
};

class RGBController {
private:
	cdMode_t cdMode;
	uint8_t speedIncrement;
public:
	void updateInfo(LightContInfo& info);

	void begin(const uint8_t intPin, TwoWire* wire);

    RGBController();
    ~RGBController();
};

#endif