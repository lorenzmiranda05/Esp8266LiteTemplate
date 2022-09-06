### **ESP8266 ESP-01 Template**
Template to be used for ESP8266-based boards with small flash memory.

---
<br  />

**data>config.json**
1. The config.json file looks like this:
    ```
    {
        "deviceType" : "ESP01",
        "accessPoint" : [
                            {
                                "ssid": "WiFi1",
                                "password": "12345"
                            },
                            {
                                "ssid": "WiFi2",
                                "password": "12345"
                            },
                            {
                                "ssid": "WiFi3",
                                "password": "12345"
                            }
                        ]
    }
    ```

<br  />

**Tasks**
* [x] Connect to WiFi using ESP8266WiFiMulti.h
* [x] Use WiFi credentials from File System
* [x] Update embedded program using ArduinoOTA.h
* [ ] Print to serial and telnet streams