//=============================================================================
//  WLANManager
//-----------------------------------------------------------------------------
//  for:    test-ESP8266
//  author: Joe Heumer
//  create: 25 October 2023
//  file:   WLANManager.cpp
//=============================================================================

#include "WLANManager.hpp"

WLANManager::WLANManager() {}
WLANManager::WLANManager(const char* ssid, const char* password) : _ssid(ssid), _password(password) {}

void WLANManager::verbindeMitWLAN() {
    if (!istWLANVerbunden()) {
        Serial.println("Verbinde mit WLAN...");
        Serial.print("SSID: " + this->getSSID() + "\n");
        Serial.print("PW  : " + this->getPassword() + "\n");

        if (_ssid == nullptr) {
            Serial.println("Es ist keine SSID vergeben");
            return;
        }

        

        if (_password == nullptr) {
            WiFi.begin(_ssid.c_str());
        }
        else {
            WiFi.begin(_ssid.c_str(), _password.c_str());
        }

        int versuche = 0;
        while (!istWLANVerbunden() && versuche < 10) {
            delay(1000);
            Serial.print(".");
            versuche++;
        }

        if (istWLANVerbunden()) {
            Serial.println("\nWLAN verbunden!");

            Serial.print("[WLAN][CONNECT] IP-Address: " + WiFi.localIP().toString() + "\n");
            Serial.print("[WLAN][CONNECT] Gateway:    " + WiFi.gatewayIP().toString() + "\n");
            Serial.print("[WLAN][CONNECT] Hostname:   " + String(WiFi.getHostname()) + "\n");

            WiFi.softAPdisconnect(true);
        } else {
            Serial.println("\nVerbindung mit WLAN fehlgeschlagen nach 10 Versuchen.");
            WiFi.softAP("ESP Konfiguration");
        }
    }
}

bool WLANManager::istWLANVerbunden() {
    return WiFi.status() == WL_CONNECTED;
}

String WLANManager::getSSID() {
    return String(this->_ssid);
}

String WLANManager::getPassword() {
    if (this->_password == "\0") {
        return "(No Password)";
    }
    return String(this->_password);
}

String WLANManager::getWifiMac() {
    return WiFi.macAddress();
}

String WLANManager::getIPAdress() {
    return WiFi.localIP().toString();
}

wl_status_t WLANManager::status() {
    return WiFi.status();
}


void WLANManager::setSSID(String ssid) {
    this->_ssid = ssid;
}

void WLANManager::setPassword(String password) {
    this->_password = password;
}

WLANManager wlan;




//=============================================================================
// End of File
//=============================================================================