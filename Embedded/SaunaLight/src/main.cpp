#include <Arduino.h>
#include "Network.h"
#include "WebServer.h"
#include "UpdateService.h"
#include "LedStrip.h"

LedStrip strip(120);
LightContInfo lightInfo;

Network network(234);
WebServer server(&lightInfo);
UpdateService* update;

void setup() {
  	Serial.begin(115200);
	Serial.println("\nSauna Light Controller\n");

	network.connect();
	update = new UpdateService("ESP-Sauna");

	server.start();
}

bool emitUpdate = false;

void loop() {
	update->loop();

	if(lightInfo.update) {
		strip.turnOnOff(lightInfo.onOff);
		strip.setTarget(lightInfo.color.h, lightInfo.color.v, lightInfo.color.w);
		strip.setWhiteMode(lightInfo.whiteMode);
		if(lightInfo.fan) digitalWrite(D8, 1);
		else digitalWrite(D8, 0);

		lightInfo.update = false;
		emitUpdate = true;
	}
	
	if(strip.getOnOff()) {
		strip.followTarget();
	}

	unsigned long currentTime = millis();

	if((currentTime % 10000) == 0) server.webSocketCleanUp();
	if((currentTime % 500) == 0 && emitUpdate) { server.syncLights(); emitUpdate = false; }
}