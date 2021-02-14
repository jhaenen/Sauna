#include "RGBController.h"

#include <Arduino.h>
#include <queue>

const uint8_t addr  = 0x53;
std::queue<ContEvent> eventQueue;
TwoWire* theWire;

void ICACHE_RAM_ATTR receiveData() {
    theWire->begin(4, 5);
    uint8_t numRec = theWire->requestFrom(addr, (uint8_t)6);

    uint8_t buff[numRec];
  
    theWire->readBytes(buff, numRec);

    if(buff[ACTION_INDEX] != BUTTON_ACTION || buff[BUTTON_INDEX] != RELEASE_BUTTON) eventQueue.emplace(buff[ACTION_INDEX], buff[BUTTON_INDEX], buff[WIPER_INDEX]);
}

volatile indicator_t currentIndicator;

void ICACHE_RAM_ATTR timerISR() {
	static volatile int8_t i = 8;
	static volatile uint8_t p = 0;

	if(i == 8) {
		digitalWrite(15, 0);
		i--;
		timer1_write(INIT_PULSE * 5);
	} else
    if(i == -1) { //Reset line
		i = 8;
		digitalWrite(15, 1);
		if(currentIndicator != OFF_INDICATOR) {
			currentIndicator = OFF_INDICATOR;
			timer1_write(OFF_DELAY * 5);
		}
	} else {
		uint8_t curBit = (currentIndicator >> i) & 1;

		if(p == 0) {
			digitalWrite(15, 1);
			p = 1;
			if(curBit == 1) timer1_write(LONG_PULSE * 5);
			else timer1_write(SHORT_PULSE * 5);
		} else {
			digitalWrite(15, 0);
			p = 0;
			i--;
			if(curBit == 1) timer1_write(SHORT_PULSE * 5);
			else timer1_write(LONG_PULSE * 5);
		}
	}
}

void setIndicator(const indicator_t indicator) {
	currentIndicator = indicator;
    timer1_write(1);
    // digitalWrite(15, 0);
    // timer1_write(INIT_PULSE * 5);
}

void RGBController::updateInfo(LightContInfo& info) {
    for(uint8_t i = 0; i < 20; i++) {
        if(eventQueue.empty()) break;
        ContEvent event = eventQueue.front();
        eventQueue.pop();

        if(event.actionType == BUTTON_ACTION) {
            switch(event.buttonType) {
                case RGB_BUTTON:
                    if(info.onOff) {
                        if(info.whiteMode) {
                            info.whiteMode = false;
                            info.update = true;
                        }
                        cdMode = COLOR_MODE;
                        setIndicator(RGB_INDICATOR);
                    }
                break;

                case DIM_BUTTON:
                    if(info.onOff) cdMode = DIM_MODE;
                    setIndicator(DIM_INDICATOR);
                break;
                
                case WHITE_BUTTON:
                    if(info.onOff) {
                        info.whiteMode = !info.whiteMode;
                        if(info.whiteMode) cdMode = DIM_MODE;
                        info.update = true;
                    }
                break;
                
                case SPEEDUP_BUTTON:
                    if(info.onOff) {
                        info.speed += speedIncrement;
                        if(info.speed > 100) info.speed = 100;
                        info.update = true;
                    }
                break;
                
                case SPEEDDOWN_BUTTON:
                    if(info.onOff) {
                        info.speed -= speedIncrement;
                        if(info.speed > 100) info.speed = 0;
                        info.update = true;
                    }
                break;
                
                case MODE_BUTTON:

                break;        
                
                case ONOFF_BUTTON:
                    info.onOff = !info.onOff;
                    info.update = true;
                    setIndicator(ON_INDICATOR);
                break;
                
                default: break;
            }

        } else if(event.actionType == WIPER_ACTION && info.onOff) {
            if(cdMode == COLOR_MODE && !(info.whiteMode)) info.color.h = COLOR_OFFSET - map(event.wiperData, 2, 210, 0, 240);
            if(cdMode == DIM_MODE) {
                uint8_t val = map(event.wiperData, 2, 210, 0, 255);
                if(info.whiteMode) info.color.w = val;
                else info.color.v = val;
            }
            info.update = true;
        }
    }
}

RGBController::RGBController() {}

void RGBController::begin(const uint8_t intPin, TwoWire* wire) {
    theWire = wire;
    wire->begin();
    pinMode(intPin, INPUT_PULLUP);
    attachInterrupt(intPin, receiveData, FALLING);
    timer1_attachInterrupt(timerISR);
	timer1_enable(TIM_DIV16, TIM_EDGE, TIM_SINGLE);

    wire->beginTransmission(addr);
    wire->write(0xBD);
    wire->write(0x39);
    wire->write(0x05);
    wire->write(0x00);
    wire->endTransmission();

    for(uint8_t i = 0; i <= 5; i++) {
        wire->beginTransmission(addr);
        wire->write(0xC0 + i);
        wire->write(0x15);
        wire->write(0x00);
        wire->endTransmission();
    }

    for(uint8_t i = 0; i <= 5; i++) {
        wire->beginTransmission(addr);
        wire->write(0xC6 + i);
        wire->write(0x45);
        wire->write(0x00);
        wire->endTransmission();
    }
}

RGBController::~RGBController() {

}