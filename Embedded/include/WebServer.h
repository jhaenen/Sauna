#ifndef WEBSERVER_H_
#define WEBSERVER_H_

#include <stdint.h>
#include <ESPAsyncWebServer.h>

#include "dt.h"

class WebServer {
private:
    AsyncWebServer* server;
    AsyncWebSocket* websocket;
    LightContInfo* lightInfo;
    uint32_t updateID = 0;
    float temp;
    float hum;
public:
    void start() { server->begin(); }
    void stop() { server->end(); }
    void webSocketCleanUp() { websocket->cleanupClients(); }

    void refreshSensorStats(const float temp, const float hum);
    void syncLights();

    WebServer(LightContInfo* info, uint16_t port = 80);
    ~WebServer();
};

#endif