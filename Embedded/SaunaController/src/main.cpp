#include <Arduino.h>
#include <ArduinoJson.h>

#include "Network.h"
#include "UpdateService.h"
#include "RGBController.h"
#include <WebSocketsClient.h>

LightContInfo lightInfo;

Network network(233);
UpdateService* update;
WebSocketsClient websocket;
RGBController rgbCont;
bool fanUpdate = false;

void websocketEvent(WStype_t type, uint8_t * payload, size_t length) {
	StaticJsonDocument<200> doc;

	switch(type) {
		case WStype_DISCONNECTED:
			Serial.println("[WSc] Disconnected!");
			break;
		case WStype_CONNECTED:
			Serial.printf("[WSc] Connected to url: %s\n", payload);
			break;
		case WStype_TEXT:			
			deserializeJson(doc, payload, length);
			lightInfo.color.h = doc["lights"]["color"]["h"];
			lightInfo.color.v = doc["lights"]["color"]["v"];
			lightInfo.color.w = doc["lights"]["color"]["w"];
			lightInfo.whiteMode = doc["lights"]["whiteMode"];
			lightInfo.fan = doc["lights"]["fan"];
			lightInfo.onOff = doc["lights"]["onOff"];
			lightInfo.speed = doc["lights"]["speed"];
			fanUpdate = true;
			break;
		default:
			break;
	}

}

void setup() {
	Serial.begin(115200);
	Serial.println("\nSauna Controller\n");
	pinMode(D8, OUTPUT);
	digitalWrite(D8, 0);
	
	network.connect();
	update = new UpdateService("ESP-Sauna");

	TwoWire* Wire1 = new TwoWire();	
	rgbCont.begin(0, Wire1);

	websocket.begin("192.168.2.234", 80, "/websocket");
	websocket.onEvent(websocketEvent);
	websocket.setReconnectInterval(5000);
}

bool emitUpdate = false;

void loop() {
	update->loop();
	websocket.loop();
	rgbCont.updateInfo(lightInfo);

	if((millis() % 500) == 0 && lightInfo.update) { 
		char buf[150];
		snprintf(buf, 150, "{\"lights\":{\"onOff\":%s,\"color\":{\"h\":%u,\"v\":%u,\"w\":%u},\"speed\":%u,\"whiteMode\":%s,\"fan\":%s}}",
						(lightInfo.onOff) ? "true" : "false", lightInfo.color.h, lightInfo.color.v, lightInfo.color.w, lightInfo.speed, (lightInfo.whiteMode) ? "true" : "false", (lightInfo.fan) ? "true" : "false");
		websocket.sendTXT(buf);
		lightInfo.update = false; 
	}

	if(fanUpdate) {
		digitalWrite(D8, (lightInfo.fan) ? 1 : 0);
		fanUpdate = false;
	}
}

