#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include "LedStrip.h"
#include "RGBController.h"

Adafruit_BME280 bme;
LedStrip strip(120);

RGBController rgbCont(13);

void setup() {
	Serial.begin(115200);
	Serial.println("\nSauna Controller\n");	
	if (! bme.begin(0x76, &Wire)) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
    }

	bme.setSampling(Adafruit_BME280::MODE_FORCED,
                    Adafruit_BME280::SAMPLING_X1, // temperature
                    Adafruit_BME280::SAMPLING_X1, // pressure
                    Adafruit_BME280::SAMPLING_X1, // humidity
                    Adafruit_BME280::FILTER_OFF   );

	bme.takeForcedMeasurement(); // has no effect in normal mode
	Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();
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

