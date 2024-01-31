//=============================================================================
//  timeNTP
//-----------------------------------------------------------------------------
//  for:    chickenCoop
//  author: Joe Heumer
//  create: 30 January 2024
//  file:   timeNTP.cpp
//=============================================================================

#include "timeNTP.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600 * 1, 600000); // Zeitzone auf 1 (UTC) gesetzt, Update-Intervall auf 10 Minuten

unsigned long lastNtpUpdateTime = 0;

void timeSynchroLoop() {
if (WiFi.status() == WL_CONNECTED) {
        if ((millis() - lastNtpUpdateTime > 600000) || lastNtpUpdateTime == 0) { // 600000 Millisekunden sind 10 Minuten
            timeClient.update();
            setTime(timeClient.getEpochTime());
            lastNtpUpdateTime = millis();
        }
    }
}




//=============================================================================
// End of File
//=============================================================================