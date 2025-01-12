#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <FS.h>

struct CommandReceive
{
    char command[5];
    uint8_t velocity;
};

struct SendData
{
    char pose[3];
};

class WiFiManager 
{
    private:
        ESP8266WebServer server;
        CommandReceive commandData;
        void handleClient();
        void handleRobotStatus();
        void handleRobotControl();
        void handleRoot();

    public:
        WiFiManager();
        ~WiFiManager()= default;

        void begin(const char *ssid, const char *password);
};

#endif // WIFIMANAGER_H
