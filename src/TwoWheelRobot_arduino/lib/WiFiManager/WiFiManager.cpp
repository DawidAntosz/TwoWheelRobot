#include "WiFiManager.hpp"

WiFiManager::WiFiManager() : server(80), 
    commandData{{'\0', '\0', '\0', '\0', '\0'}, 0}
{
}

void WiFiManager::begin(const char *ssid, const char *password)
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(700);
        Serial.print(".");
    }

    Serial.print("Connected! IP address: ");
    Serial.println(WiFi.localIP());

    server.serveStatic("/style.css", LittleFS, "/style.css");
    server.serveStatic("/src/", LittleFS, "/src/");

    server.on("/", HTTP_GET, [this]() { handleRoot(); });
    server.on("/robot-control", HTTP_POST, [this]() { handleRobotControl(); });
    server.on("/robot-status", HTTP_GET, [this]() { handleRobotStatus(); });

    server.begin();

    if (!LittleFS.begin()) 
    {
        Serial.println("Failed to mount LittleFS");
        return;
    }

    // wifiTimer.attach_ms(TIMER_INTERVAL_WIFI_MS, [this]() { this->wifiTimerCallback(); });
}

void WiFiManager::wifiTimerCallback(void)
{
    if (WiFi.status() == WL_CONNECTED) {
        server.handleClient();
        delay(10);
        yield();
    }
}

void WiFiManager::handleServer(void)
{
    server.handleClient();
}

void WiFiManager::handleRoot()
{
    File file = LittleFS.open("/index.html", "r");

    if (!file) 
    {
        Serial.println("Failed to open index.html");
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

void WiFiManager::listFiles(void)
{
    Serial.println("Listing files in LittleFS:");
    Dir dir = LittleFS.openDir("/");

    while (dir.next()) 
    {
        Serial.print("File: ");
        Serial.print(dir.fileName());
        Serial.print(", Size: ");
        Serial.println(dir.fileSize());
    }
}
