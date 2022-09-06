#include <FS.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wm;

#define JsonConfigFile "/config.json"
bool addApFromConfigFile()
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
            serializeJsonPretty(json, Serial);
            // serializeJsonPretty(json, TelnetStream);
            if (!error)
            {
                Serial.println(F(""));
                Serial.println(F("Parsing"));
                wm.addAP(json[0]["SSID"], json[0]["Password"]);
                wm.addAP(json[1]["SSID"], json[1]["Password"]);
                wm.addAP(json[2]["SSID"], json[2]["Password"]);

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