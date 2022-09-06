#include <Arduino.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wm;

void setup()
{
  Serial.begin(921600);
  delay(10);
  wm.addAP("SSID1", "Password1");
  wm.addAP("SSID2", "Password2");
  wm.addAP("SSID3", "Password3");
}

void loop()
{
  if (wm.run() != WL_CONNECTED)
  {
    Serial.println("WiFi not connected!");
    delay(5000);
  }
  if (wm.run() == WL_CONNECTED)
  {
    Serial.println("");
    Serial.print("WiFi connected to ");
    Serial.println(WiFi.SSID());
    Serial.print("IP Address ");
    Serial.println(WiFi.localIP());
    delay(5000);
  }