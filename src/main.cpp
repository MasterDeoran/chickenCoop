// #include <Arduino.h>
// #include "manager/EEPROMManager.hpp"
// #include "manager/WebsiteManager.hpp"
// #include "manager/WLANManager.hpp"



// void setup()
// {
//     // put your setup code here, to run once:
//     Serial.begin(115200);
//     EEPROMManager::initialize();
//     //WiFi.setHostname("ESP-041369");
//     website.initialize();
//     Serial.println("Start des Microcontrollers22");
// }

// void loop()
// {
//     website.loop();

//     if (website.isInitialize()) {
//         wlan.verbindeMitWLAN();
//         delay(100);
//     }

//     delay(100);

//     // put your main code here, to run repeatedly:
// }


 /*
  AsyncElegantOTA Demo Example - This example will work for both ESP8266 & ESP32 microcontrollers.
  -----
  Author: Ayush Sharma ( https://github.com/ayushsharma82 )
  
  Important Notice: Star the repository on Github if you like the library! :)
  Repository Link: https://github.com/ayushsharma82/AsyncElegantOTA
*/

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
  Serial.println("");

}

void loop(void) {
    website.loop();
    timeSynchroLoop();

    if (website.isInitialize()) {
        wlan.verbindeMitWLAN();
        delay(100);
    }
}