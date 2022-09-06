#include <FS.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoOTA.h>

#define JsonConfigFile "/config.json"

ESP8266WiFiMulti wm;
char espName[15];

#define JsonConfigFile "/config.json"
bool loadConfigFile()
// Load existing configuration file
{
    // Uncomment if we need to format filesystem
    // LittleFS.format();

    // Read configuration from FS json
    Serial.println(F("Mounting FS"));

    // May need to make it begin(true) first time you are using SPIFFS
    if (LittleFS.begin())
    {
        // The file exists, reading and loading
        Serial.println(F("Reading config"));
        File configFile = LittleFS.open(JsonConfigFile, "r");
        if (configFile)
        {
            Serial.println(F("Opened config"));
            StaticJsonDocument<512> json;
            DeserializationError error = deserializeJson(json, configFile);
            //  serializeJsonPretty(json, Serial);
            //  serializeJsonPretty(json, TelnetStream);
            if (!error)
            {
                // Serial.println(F(""));
                Serial.println(F("Parsing config"));
                strcpy(espName, json["deviceType"]);
                wm.addAP(json["accessPoint"][0]["ssid"], json["accessPoint"][0]["password"]);
                wm.addAP(json["accessPoint"][1]["ssid"], json["accessPoint"][1]["password"]);
                wm.addAP(json["accessPoint"][2]["ssid"], json["accessPoint"][2]["password"]);

                return true;
            }
            else
            {
                // Error loading JSON data
                Serial.println(F("Load config failed"));
            }
        }
    }
    else
    {
        // Error mounting file system
        Serial.println(F("Mount FS failed"));
    }
    return false;
}

void setupOTA()
{
    // Create unique ota host name by appending MAC Address
    uint16_t maxlen = strlen(espName) + 8;
    char *deviceName = new char[maxlen];
    uint8_t mac[6];
    WiFi.macAddress(mac);
    snprintf(deviceName, maxlen, "%s-%02x%02x%02x", espName, mac[3], mac[4], mac[5]);
    strcpy(espName, deviceName);
    ArduinoOTA.setHostname(deviceName);
    delete[] deviceName;

    ArduinoOTA.onStart([]()
                       {
                            Serial.print(F(""));
                            Serial.println(F("Update start")); });

    ArduinoOTA.onEnd([]()
                     { Serial.println(F("\nEnd")); });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                          { Serial.printf("Progress: %u%%\r", (progress / (total / 100))); });

    ArduinoOTA.onError([](ota_error_t error)
                       {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println(F("\nAuth Failed"));
        else if (error == OTA_BEGIN_ERROR) Serial.println(F("\nBegin Failed"));
        else if (error == OTA_CONNECT_ERROR) Serial.println(F("\nConnect Failed"));
        else if (error == OTA_RECEIVE_ERROR) Serial.println(F("\nReceive Failed"));
        else if (error == OTA_END_ERROR) Serial.println(F("\nEnd Failed")); });

    ArduinoOTA.begin();
    Serial.println(F("ESPOTA READY"));
}