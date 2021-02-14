#include "WebServer.h"

#include <LittleFS.h>

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len, uint32_t id) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    char buff[50];
    snprintf(buff, 50, "Client %u sent data: %s", id, (char*)data);
    Serial.println(buff);
    //ws.textAll(buff);
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    switch (type) {
      case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        break;
      case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
      case WS_EVT_DATA:
        handleWebSocketMessage(arg, data, len, client->id());
        break;
      case WS_EVT_PONG:
      case WS_EVT_ERROR:
        break;
  }
}

void WebServer::refreshSensorStats(float temp, float hum) {
    char buf[50];
    snprintf(buf, 50, "{\"sensor\":{\"temp\":%.2f,\"hum\":%.2f}}", temp, hum);
	// ,\"lights\":{\"onOff\":%s,\"color\":{\"h\":%u,\"v\":%u,\"w\":%u},\"speed\":%u,\"whiteMode\":%s}}",
                        	// temp, hum, (lightInfo->onOff) ? "true" : "false", lightInfo->color.h, lightInfo->color.v, lightInfo->color.w, lightInfo->speed, (lightInfo->whiteMode) ? "true" : "false");

    websocket->textAll(buf);
}

void WebServer::syncLights() {
	char buf[100];
    snprintf(buf, 100, "{\"lights\":{\"onOff\":%s,\"color\":{\"h\":%u,\"v\":%u,\"w\":%u},\"speed\":%u,\"whiteMode\":%s}}",
						(lightInfo->onOff) ? "true" : "false", lightInfo->color.h, lightInfo->color.v, lightInfo->color.w, lightInfo->speed, (lightInfo->whiteMode) ? "true" : "false");

    websocket->textAll(buf);
}

WebServer::WebServer(LightContInfo* info, uint16_t port) {
    server = new AsyncWebServer(port);
    lightInfo = info;

    // Initialize LittleFS
    if(!LittleFS.begin()){
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }

    server->on("/stats", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/stats.json", String(), false);
    });

    server->on("/setLight", HTTP_GET, [this](AsyncWebServerRequest *request) {
        if(request->hasParam("h") && request->hasParam("v")) {
            lightInfo->color.h = request->getParam("h")->value().toInt();
            lightInfo->color.v = request->getParam("v")->value().toInt();
            lightInfo->whiteMode = false;
            lightInfo->onOff = true;

            lightInfo->update = true;
            request->send(200, "text/plain", "Color is set!");
        } else if(request->hasParam("w")) {
            lightInfo->color.w = request->getParam("w")->value().toInt();
            lightInfo->whiteMode = true;
            lightInfo->onOff = true;

            lightInfo->update = true;
            request->send(200, "text/plain", "Color is set!");
        } else request->send(400, "text/plain", "Please provide valid parameters");
    });

    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");

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
    websocket->onEvent(onEvent);
    server->addHandler(websocket);
}

WebServer::~WebServer() {
    server->end();
    delete server;
    delete websocket;
}