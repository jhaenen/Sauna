#include "WebServer.h"

#include <LittleFS.h>

void WebServer::refreshStats(float temp, float hum) {
    File stats = LittleFS.open("stats.json", "w");

    stats.printf("{\"temp\": %.2f, \"hum\": %.2f}", temp, hum);

    stats.close();
}

WebServer::WebServer(uint16_t port) {
    server = new AsyncWebServer(port);

    // Initialize LittleFS
    if(!LittleFS.begin()){
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }

    server->on("/stats", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/stats.json", String(), false);
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