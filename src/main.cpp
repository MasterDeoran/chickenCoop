
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
  website.initialize();
  Serial.println("Start des Microcontrollers");

}

void loop(void) {
    website.loop();
    timeSynchroLoop();

    if (website.isInitialize()) {
        wlan.verbindeMitWLAN();
        delay(100);
    }
}