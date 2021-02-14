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
public:
    void start() { server->begin(); }
    void stop() { server->end(); }
    void webSocketCleanUp() { websocket->cleanupClients(); }

    void refreshSensorStats(float temp, float hum);
    void syncLights();

    WebServer(LightContInfo* info, uint16_t port = 80);
    ~WebServer();
};

#endif