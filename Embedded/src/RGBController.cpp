#include "RGBController.h"

#include <Arduino.h>
#include <Wire.h>
#include <queue>

const uint8_t addr  = 0x53;
std::queue<ContEvent> eventQueue;

void ICACHE_RAM_ATTR receiveData() {
    uint8_t rec = 0;
    Wire.requestFrom((int)addr, 6);

    uint8_t buff[10];
  
    while(Wire.available()) {
        buff[rec] = Wire.read();
        rec++;
    }

    if(buff[ACTION_INDEX] != BUTTON_ACTION || buff[BUTTON_INDEX] != RELEASE_BUTTON) eventQueue.emplace(buff[ACTION_INDEX], buff[BUTTON_INDEX], buff[WIPER_INDEX]);
}

RGBContInfo* RGBController::updateInfo() {
    for(uint8_t i = 0; i < 20; i++) {
        if(eventQueue.empty()) break;
        ContEvent event = eventQueue.front();
        eventQueue.pop();

        if(event.actionType == BUTTON_ACTION) {
            switch(event.buttonType) {
                case RGB_BUTTON:
                if(info.onOff) {
                    if(info.whiteMode) info.whiteMode = false;
                    cdMode = COLOR_MODE;
                }
                break;

                case DIM_BUTTON:
                if(info.onOff) cdMode = DIM_MODE;
                break;
                
                case WHITE_BUTTON:
                if(info.onOff) {
                    info.whiteMode = !info.whiteMode;
                    if(info.whiteMode) cdMode = DIM_MODE;
                }
                break;
                
                case SPEEDUP_BUTTON:
                    if(info.onOff) {
                        info.speed += speedIncrement;
                        if(info.speed > 100) info.speed = 100;
                    }
                break;
                
                case SPEEDDOWN_BUTTON:
                    if(info.onOff) {
                        info.speed -= speedIncrement;
                        if(info.speed > 100) info.speed = 0;
                    }
                break;
                
                case MODE_BUTTON:

                break;        
                
                case ONOFF_BUTTON:
                    info.onOff = !info.onOff;
                break;
                
                default: break;
            }

        } else if(event.actionType == WIPER_ACTION && info.onOff) {
            if(cdMode == COLOR_MODE && !(info.whiteMode)) info.color.h = COLOR_OFFSET - map(event.wiperData, 2, 210, 0, 240);
            if(cdMode == DIM_MODE) info.color.v = map(event.wiperData, 2, 210, 0, 255);
        }
    }
    
    return &info;
}

RGBController::RGBController(const uint8_t intPin) {
    Wire.begin();
    pinMode(intPin, INPUT_PULLUP);
    attachInterrupt(intPin, receiveData, FALLING);

    Wire.beginTransmission(addr);
    Wire.write(0xBD);
    Wire.write(0x39);
    Wire.write(0x05);
    Wire.write(0x00);
    Wire.endTransmission();

    for(uint8_t i = 0; i <= 5; i++) {
        Wire.beginTransmission(addr);
        Wire.write(0xC0 + i);
        Wire.write(0x15);
        Wire.write(0x00);
        Wire.endTransmission();
    }

    for(uint8_t i = 0; i <= 5; i++) {
        Wire.beginTransmission(addr);
        Wire.write(0xC6 + i);
        Wire.write(0x45);
        Wire.write(0x00);
        Wire.endTransmission();
    }
}



RGBController::~RGBController() {

}