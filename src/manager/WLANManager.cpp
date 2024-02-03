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

void WLANManager::verbinde() {
    this->verbindeMitWLAN();
    // Wenn erfolgreich verbunden, schließe den SoftAP (wenn aktiviert) und wechsle zu WIFI_STATE_CONNECTED
    if (WiFi.status() == WL_CONNECTED) {
        this->closeSoftAP();
        Serial.println("[WIFI][MODE] CHANGE MODE => WIFI_STATE_CONNECTED");
        this->_state = WIFI_STATE_CONNECTED;
    }
    // Wenn keine Verbindung hergestellt wurde, öffne den SoftAP
    else this->openSoftAP();
}

void WLANManager::verbindeMitWLAN() {
    if (!istWLANVerbunden()) {
        Serial.println("Verbinde mit WLAN...");
        Serial.print("SSID: " + this->getSSID() + "\n");
        Serial.print("PW  : " + this->getPassword() + "\n");

        if (_ssid.isEmpty()) {

            Serial.println("[WIFI][CONN] Keine SSID vergeben...versuch aus EEPROM zu lesen");
            this->_ssid = EEPROMManager::leseWlanSSID();
            this->_password = EEPROMManager::leseWlanPassword();

            if (_ssid.isEmpty()) {
                Serial.println("Es ist keine SSID vergeben");
                return;
            }

        }

        if (_password.isEmpty()) {
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

            //WiFi.softAPdisconnect(true);
        } else {
            Serial.println("\nVerbindung mit WLAN fehlgeschlagen nach 10 Versuchen.");
            //WiFi.softAP("ESP Konfiguration");
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

void WLANManager::setOn(void) {
    this->_enabled = true;
}
void WLANManager::setOff(void) {
    this->_enabled = false;
}

void WLANManager::initializeSoftAP(void) {
    this->local_IP = AP_LOCAL_IP;
    this->gateway = AP_GATEWAY;
    this->subnet = AP_SUBNET;
    this->espName = AP_SSID;

    Serial.printf("[WIFI][S-AP] Local-IP: %s\n", this->local_IP.toString().c_str());
    Serial.printf("[WIFI][S-AP] Gateway : %s\n", this->gateway.toString().c_str());
    Serial.printf("[WIFI][S-AP] Subnet  : %s\n", this->subnet.toString().c_str());
    Serial.printf("[WIFI][S-AP] ESP-Name: %s\n", this->espName.c_str());

    // Konfiguriere den SoftAP-Modus mit der statischen IP
    if (!WiFi.softAPConfig(this->local_IP, this->gateway, this->subnet))
    {
        Serial.println("SoftAP Konfiguration fehlgeschlagen!");
    }

    Serial.println("[WIFI][MODE] Start SoftAP");
    // Aktiviere den SoftAP-Modus
    WiFi.softAP(this->espName.c_str());
    
}

void WLANManager::openSoftAP() { 
    // Überprüfe, ob der SoftAP-Modus bereits aktiv ist
    if (WiFi.getMode() != WIFI_AP) {
        // Deaktiviere den normalen WLAN-Modus (WIFI_STA)
        Serial.println("[WIFI][MODE] Close WIFI");
        WiFi.mode(WIFI_OFF);
        
        // Warte einen Moment, um sicherzustellen, dass der WLAN-Modus deaktiviert ist
        delay(100); 
        Serial.println("[WIFI][MODE] Start SoftAP");
        // Aktiviere den SoftAP-Modus
        WiFi.softAP(this->espName.c_str());
    }

}
void WLANManager::closeSoftAP() { 
    // Deaktiviere den SoftAP-Modus und aktiviere den normalen WLAN-Modus (WIFI_STA)
    // Überprüfe, ob der SoftAP-Modus bereits aktiv ist
    if (WiFi.getMode() == WIFI_AP) {
        // Warte einen Moment, um sicherzustellen, dass der SoftAP-Modus deaktiviert ist
        delay(100);
        // Aktiviere den normalen WLAN-Modus (WIFI_STA)
        Serial.println("[WIFI][MODE] Close SoftAP");
        WiFi.mode(WIFI_STA);
    }
}

// Methode zum Aktualisieren des WLAN-Status
void WLANManager::update() {

    unsigned long currentMillis = millis();

    switch (this->_state) {
        // Wenn die Wartezeit abgelaufen ist, wechsle zum WIFI_STATE_DISCONNECTED-Status und aktiviere den SoftAP
        case mwifi_state_t::WIFI_STATE_WAITING_FOR_CONNECTION: 
            if (currentMillis > startAutoWlanTime) {
                Serial.println("[WIFI][MODE] CHANGE MODE => WIFI_STATE_DISCONNECTED");
                this->_state = mwifi_state_t::WIFI_STATE_DISCONNECTED;
            }
            break;

        // Versuche, sich alle _wifiInterval Millisekunden mit dem WLAN zu verbinden
        case mwifi_state_t::WIFI_STATE_DISCONNECTED: 
            if (currentMillis - this->_lastConnect > this->_wifiInterval) {
                this->_lastConnect = currentMillis;
                this->verbinde();
            }

            break;
        case mwifi_state_t::WIFI_STATE_CONNECTED:
            // Überprüfe, ob die Verbindung zum WLAN verloren gegangen ist
            if (WiFi.status() != WL_CONNECTED) {
                // Wenn die Verbindung verloren geht, öffne den SoftAP erneut und wechsle zu WIFI_STATE_DISCONNECTED
                Serial.println("[WIFI][MODE] CHANGE MODE => WIFI_STATE_DISCONNECTED");
                this->_state = WIFI_STATE_DISCONNECTED;
                this->openSoftAP();
            }
            break;
    }
}

WLANManager wlan;




//=============================================================================
// End of File
//=============================================================================