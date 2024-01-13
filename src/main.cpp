#include <Arduino.h>
#include "manager/EEPROMManager.hpp"
#include "manager/WebsiteManager.hpp"
#include "manager/WLANManager.hpp"
#include "manager/SensorManager.hpp"


void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    EEPROMManager::initialize();
    //WiFi.setHostname("ESP-041369");
    website.initialize();
    Serial.println("Start des Microcontrollers");
    Sensor.initialize();
}

void loop()
{
    website.loop();
    Sensor.loop();
    if (website.isInitialize()) {
        wlan.verbindeMitWLAN();
        delay(100);
    }

    delay(100);

    // put your main code here, to run repeatedly:
    
}