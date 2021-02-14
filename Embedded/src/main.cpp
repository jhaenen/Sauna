#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include "Network.h"
#include "WebServer.h"
#include "LedStrip.h"
#include "RGBController.h"

Adafruit_BME280 bme;
LedStrip strip(120);
LightContInfo lightInfo;

Network network(233);
WebServer server(&lightInfo);

RGBController rgbCont;

void measure() {
	bme.takeForcedMeasurement(); // has no effect in normal mode
	float temp = bme.readTemperature();
	float hum = bme.readHumidity();
    
	// server.refreshStats(temp, hum);
}

void setup() {
	Serial.begin(115200);
	Serial.println("\nSauna Controller\n");
	
	pinMode(15, OUTPUT);
	digitalWrite(15, 1);
	
	network.connect();	

	server.start();

	TwoWire* Wire2 = new TwoWire();	

	TwoWire* Wire1 = new TwoWire();	
	rgbCont.begin(0, Wire1);

	if(!bme.begin(0x76, Wire2, 12, 14)) {
		Serial.println("Could not find a valid BME280 sensor, check wiring!");
	}

	bme.setSampling(Adafruit_BME280::MODE_FORCED,
					Adafruit_BME280::SAMPLING_X1, // temperature
					Adafruit_BME280::SAMPLING_X1, // pressure
					Adafruit_BME280::SAMPLING_X1, // humidity
					Adafruit_BME280::FILTER_OFF   );

	measure();
}

void loop() {
	rgbCont.updateInfo(lightInfo);

	if(lightInfo.update) {
		strip.turnOnOff(lightInfo.onOff);
		strip.setTarget(lightInfo.color.h, lightInfo.color.v, lightInfo.color.w);
		strip.setWhiteMode(lightInfo.whiteMode);
		lightInfo.update = false;
	}
	
	if(strip.getOnOff()) {
		strip.followTarget();
	}
	
	if((millis() % 5000) == 0) {
		measure();
	}
}

