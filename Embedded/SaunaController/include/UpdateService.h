#ifndef UPDATE_SERVICE_H_
#define UPDATE_SERVICE_H_

#include <ArduinoOTA.h>
#include <LittleFS.h>

class UpdateService {
public:
    void loop();
    UpdateService(const char* hostName = "", uint16_t port = 8266);
};

UpdateService::UpdateService(const char* hostName, uint16_t port) {
    if(hostName != (const char*)"") ArduinoOTA.setHostname(hostName);

	ArduinoOTA.onStart([](){
		String type;
		if (ArduinoOTA.getCommand() == U_FLASH)
			type = "sketch";
		else { // U_SPIFFS
			type = "filesystem";
			LittleFS.end();
		}

		Serial.println("Start updating: " + type);
		pinMode(2, OUTPUT);
	});

	ArduinoOTA.onEnd([]() { Serial.println("\nEnd"); });
	ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        static int8_t curPro = -1;
		static bool led = true;
        uint8_t procent = progress / (total / 100);
		
		if((procent % 5) == 0 && procent > curPro) {
            Serial.printf("Progress: %u%%\n", procent);
            curPro = procent;
        }

		digitalWrite(2, led);
		led = !led;
	});
	
	ArduinoOTA.onError([](ota_error_t error) {
   		Serial.printf("Error[%u]: ", error);
		if (error == OTA_AUTH_ERROR)         Serial.println("Auth Failed");
		else if (error == OTA_BEGIN_ERROR)   Serial.println("Begin Failed");
		else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
		else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
		else if (error == OTA_END_ERROR)     Serial.println("End Failed");
	});

	ArduinoOTA.begin();
}

void UpdateService::loop() {
    ArduinoOTA.handle();
    yield();
}

#endif