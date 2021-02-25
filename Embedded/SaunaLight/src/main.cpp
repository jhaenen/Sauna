#include <Arduino.h>
#include <Adafruit_BME280.h>
#include "Network.h"
#include "WebServer.h"
#include "UpdateService.h"
#include "LedStrip.h"

LedStrip strip(120);
LightContInfo lightInfo;
Adafruit_BME280 bme;
Network network(234);
WebServer server(&lightInfo);
UpdateService* update;

void measure() {
	bme.takeForcedMeasurement();
	float temp = bme.readTemperature();
	float hum = bme.readHumidity();
    
	server.refreshSensorStats(temp, hum);
}

void setup() {
  	Serial.begin(115200);
	Serial.println("\nSauna Light Controller\n");

	network.connect();
	update = new UpdateService("ESP-Sauna");

	server.start();

	if(!bme.begin(0x76)) Serial.println("Could not find a valid BME280 sensor, check wiring!");

	bme.setSampling(Adafruit_BME280::MODE_FORCED,
					Adafruit_BME280::SAMPLING_X1, // temperature
					Adafruit_BME280::SAMPLING_X1, // pressure
					Adafruit_BME280::SAMPLING_X1, // humidity
					Adafruit_BME280::FILTER_OFF   );

	measure();
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

	if((currentTime % 5000) == 0) measure();
	if((currentTime % 10000) == 0) server.webSocketCleanUp();
	if((currentTime % 500) == 0 && emitUpdate) { server.syncLights(); emitUpdate = false; }
}