#ifndef WEBSERVER_H_
#define WEBSERVER_H_

#include <stdint.h>
#include <ESPAsyncWebServer.h>

class WebServer {
private:
    AsyncWebServer* server;
public:
    void start() { server->begin(); }
    void stop() { server->end(); }
    void refreshStats(float temp, float hum);

    WebServer(uint16_t port = 80);
    ~WebServer();
};

#endif