#include <Arduino.h>
#include <Utility.h>

void setup()
{
  Serial.begin(921600);
  delay(10);
  wm.addAP("SSID1", "Password1");
  wm.addAP("SSID2", "Password2");
  wm.addAP("MindGoblin", "P@ssw0rdWLAN");
  addApFromConfigFile();
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
}