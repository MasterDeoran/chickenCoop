#include <Arduino.h>
#include "manager/EEPROMManager.hpp"
#include "manager/WebsiteManager.hpp"
#include "manager/WLANManager.hpp"



void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    EEPROMManager::initialize();
    //WiFi.setHostname("ESP-041369");
    website.initialize();
    Serial.println("Start des Microcontrollers22");
}

void loop()
{
    website.loop();

    if (website.isInitialize()) {
        wlan.verbindeMitWLAN();
        delay(100);
    }

    delay(100);

    // put your main code here, to run repeatedly:
    
}