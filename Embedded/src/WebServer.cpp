#include "WebServer.h"

#include <LittleFS.h>

void WebServer::refreshStats(float temp, float hum) {
    File stats = LittleFS.open("stats.json", "w");

    stats.printf("{\"temp\":%.2f,\"hum\":%.2f,\"lights:\":{\"onOff\":%s,\"color\":{\"h\":%u,\"v\":%u,\"w\":%u}}}", temp, hum, (lightInfo->onOff) ? "true" : "false", lightInfo->color.h, lightInfo->color.v, lightInfo->color.w);

    stats.close();
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
}

WebServer::~WebServer() {
    server->end();
    delete server;
}