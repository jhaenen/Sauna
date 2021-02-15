#include "WebServer.h"

#include <ArduinoJson.h>
#include <LittleFS.h>

void WebServer::refreshSensorStats(const float temp, const float hum) {
    char buf[50];
    this->temp = temp;
    this->hum = hum;
    snprintf(buf, 50, "{\"sensor\":{\"temp\":%.2f,\"hum\":%.2f}}", temp, hum);

    websocket->textAll(buf);
}

void WebServer::syncLights() {
	char buf[100];
    snprintf(buf, 100, "{\"lights\":{\"onOff\":%s,\"color\":{\"h\":%u,\"v\":%u,\"w\":%u},\"speed\":%u,\"whiteMode\":%s}}",
						(lightInfo->onOff) ? "true" : "false", lightInfo->color.h, lightInfo->color.v, lightInfo->color.w, lightInfo->speed, (lightInfo->whiteMode) ? "true" : "false");

    for(const auto& c: websocket->getClients()){
		if(c->status() == WS_CONNECTED && c->id() != updateID){
			c->text(buf);
		}
	}	

	updateID = 0;
}

WebServer::WebServer(LightContInfo* info, uint16_t port) {
    server = new AsyncWebServer(port);
    lightInfo = info;

    // Initialize LittleFS
    if(!LittleFS.begin()){
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }

    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/index.html", "text/html", false);
    });

    server->on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/index.html", "text/html", false);
    });

    server->on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/main.js", "application/javascript", false);
    });

    server->on("/45.main.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/45.main.js", "application/javascript", false);
    });

    server->on("/236.main.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/236.main.js", "application/javascript", false);
    });

    server->on("/309.main.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/309.main.js", "application/javascript", false);
    });

    server->on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/style.css", "text/css", false);
    });

    server->on("/45.style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/45.style.css", "text/css", false);
    });

    server->on("/309.style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/309.style.css", "text/css", false);
    });

    server->on("/assets/sauna_heater.jpg", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/assets/sauna_heater.jpg", "img/jpg", false);
    });

    server->on("/assets/sauna_verlichting.jpg", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/assets/sauna_verlichting.jpg", "img/jpg", false);
    });

    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    DefaultHeaders::Instance().addHeader("Content-Encoding", "gzip");

    server->onNotFound([](AsyncWebServerRequest *request) {
        if (request->method() == HTTP_OPTIONS) {
            AsyncWebServerResponse* response = request->beginResponse(200);
            response->addHeader("Access-Control-Allow-Headers", "content-type");
            request->send(response);
        } else {
            request->send(404);
        }
    });

    websocket = new AsyncWebSocket("/websocket");
    websocket->onEvent([this](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
		if(type == WS_EVT_CONNECT) {
			Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());

            char buf[150];
            snprintf(buf, 150, "{\"sensor\":{\"temp\":%.2f,\"hum\":%.2f},\"lights\":{\"onOff\":%s,\"color\":{\"h\":%u,\"v\":%u,\"w\":%u},\"speed\":%u,\"whiteMode\":%s}}",
						            temp, hum, (lightInfo->onOff) ? "true" : "false", lightInfo->color.h, lightInfo->color.v, lightInfo->color.w, lightInfo->speed, (lightInfo->whiteMode) ? "true" : "false");
            
            server->text(client->id(), buf);
		} else if(type == WS_EVT_DISCONNECT) {
			Serial.printf("WebSocket client #%u disconnected\n", client->id());
		} else if(type == WS_EVT_DATA) {
			AwsFrameInfo *info = (AwsFrameInfo*)arg;

			if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
				data[len] = 0;	
				updateID = client->id();

                // Serial.printf("Received: %s\n", data);

				StaticJsonDocument<128> doc;
                // DeserializationError error = 
                deserializeJson(doc, data, len);
				// if(error) {
                //     Serial.print(F("deserializeJson() failed: "));
                //     Serial.println(error.f_str());
                // }

				lightInfo->color.h = doc["lights"]["color"]["h"];
				lightInfo->color.v = doc["lights"]["color"]["v"];
				lightInfo->color.w = doc["lights"]["color"]["w"];
				lightInfo->whiteMode = doc["lights"]["whiteMode"];
				lightInfo->onOff = doc["lights"]["onOff"];
				lightInfo->speed = doc["lights"]["speed"];
				lightInfo->update = true;
			}
		}
	});

    server->addHandler(websocket);
}

WebServer::~WebServer() {
    server->end();
    delete server;
    delete websocket;
}