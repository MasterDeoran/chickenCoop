
#include <Arduino.h>
#include "manager/EEPROMManager.hpp"
#include "manager/InterfaceManager.hpp"
#include "manager/WebsiteManager.hpp"
#include "manager/WLANManager.hpp"
#include "object/timeNTP.h"

void setup(void) {
    Serial.begin(115200);
    EEPROMManager::initialize();
    IManager.initialize();
    // Initialisieren des Software Accesspoints
    delay(100);
    wlan.initializeSoftAP();
    website.initialize();
    Serial.println("Start des Microcontrollers");
    wlan.verbinde();

}

void loop(void) {
    wlan.update();
    website.loop();
    timeSynchroLoop();
    IManager.loop();

    if (wlan.istWLANVerbunden()) {
        ILedRed.setOn();
    } 
    else {
        ILedRed.setOff();
    }
    // if (website.isInitialize()) {
    //     wlan.verbindeMitWLAN();
    //     delay(100);
    // }
}