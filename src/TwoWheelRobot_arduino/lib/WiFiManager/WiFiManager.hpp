#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

struct RobotData
{
    char command;
    uint8_t velocity;
};

class WiFiManager 
{
    private:
        ESP8266WebServer server;

    public:
        WiFiManager();
        ~WiFiManager()= default;

        void begin(const char *ssid, const char *password);
}

#endif // WIFIMANAGER_H