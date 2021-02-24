#ifndef NETWORK_H_
#define NETWORK_H_

#include <ESP8266WiFi.h>

#include "_private.h"

class Network {
private:

public:
    void connect();

    Network(uint8_t ipEnding);
    ~Network();
};

Network::Network(uint8_t ipEnding) {
    IPAddress local_IP(192, 168, 2, ipEnding);
    IPAddress gateway(192, 168, 2, 254);
    IPAddress subnet(255, 255, 255, 0);
    IPAddress dns(192, 168, 2, 254);  

    // Configures static IP address
    if (!WiFi.config(local_IP, gateway, subnet, dns)) {
        Serial.println("STA Failed to configure");
    }
}

// Connect to Wi-Fi
void Network::connect() { 
    WiFi.begin(ssid, password);

    Serial.print("Connecting to WiFi.");

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    } 

    Serial.println("");

    // Print ESP8266 Local IP Address
    Serial.printf("IP address: %s\n", WiFi.localIP().toString().c_str());
}

Network::~Network() {

}


#endif