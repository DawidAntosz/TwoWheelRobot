#include "WiFiManager.hpp"

WiFiManager::WiFiManager() : server(80), 
    commandData{{'\0', '\0', '\0', '\0', '\0'}, 0}
{
}

void WiFiManager::begin(const char *ssid, const char *password)
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    server.on("/", HTTP_GET, [this]() { handleRoot(); });
    server.on("/robot-control", HTTP_POST, [this]() { handleRobotControl(); });
    server.on("/robot-status", HTTP_GET, [this]() { handleRobotStatus(); });
    server.begin();

    if (!SPIFFS.begin()) 
    {
        Serial.println("Failed to mount SPIFFS");
        return;
    }
}

void WiFiManager::handleRoot()
{
    File file = SPIFFS.open("/index.html", "r");
    
    if (!file) 
    {
        server.send(500, "text/plain", "Failed to open index.html");
        return;
    }

    server.streamFile(file, "text/html");
    file.close();
}

void WiFiManager::handleRobotControl()
{
    if (server.hasArg("plain")) {
        String body = server.arg("plain");
        Serial.println("Received data: " + body);

        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, body);

        if (error) 
        {
            Serial.print("JSON parse error: ");
            Serial.println(error.c_str());
            server.send(400, "application/json", "{\"status\":\"error\",\"message\":\"Invalid JSON\"}");
            return;
        }

        if (doc["command"].is<const char*>()) 
        {
            strncpy(commandData.command, doc["command"].as<const char*>(), sizeof(commandData.command) - 1);
            commandData.command[sizeof(commandData.command) - 1] = '\0';
        }

        if (doc["velocity"].is<uint8_t>()) 
        {
            commandData.velocity = doc["velocity"].as<uint8_t>();
        }
        server.send(200, "application/json", "{\"status\":\"success\"}");
    } 
    else 
    {
        server.send(400, "application/json", "{\"status\":\"error\",\"message\":\"No data received\"}");
    }
}

void WiFiManager::handleRobotStatus()
{
    JsonDocument doc;
    doc["command"] = String(commandData.command);
    doc["velocity"] = commandData.velocity;

    String response;
    serializeJson(doc, response);

    server.send(200, "application/json", response);
}
