#include <Arduino.h>
#include <Utility.h>

void setup()
{
  Serial.begin(921600);
  delay(10);
  loadConfigFile();
  setupOTA();
}

void loop()
{
  ArduinoOTA.handle();
  if (wm.run() != WL_CONNECTED)
  {
    Serial.println("WiFi not connected!");
    delay(5000);
  }
  if (wm.run() == WL_CONNECTED)
  {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());
    Serial.print("Device Name ");
    Serial.println(espName);
    Serial.print("IP Address ");
    Serial.println(WiFi.localIP());
    delay(5000);
  }
}