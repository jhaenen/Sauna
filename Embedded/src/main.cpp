#include <Arduino.h>

#include "LedStrip.h"
#include "RGBController.h"

LedStrip strip(120);

RGBController rgbCont(13);

void setup() {
	Serial.begin(115200);
	Serial.println("\nSauna Controller\n");	
}

void loop() {
	RGBContInfo* info = rgbCont.updateInfo();
	strip.turnOnOff(info->onOff);
	if(info->onOff) {
		strip.setTarget(info->color.h, info->color.v);
		strip.setWhiteMode(info->whiteMode);
		strip.followTarget();
	}
	
}

