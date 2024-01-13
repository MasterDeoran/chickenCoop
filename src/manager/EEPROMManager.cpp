//=============================================================================
//  EEPROM
//-----------------------------------------------------------------------------
//  for:    EMS-standalone
//  author: Joe Heumer
//  create: 01 December 2023
//  file:   EEPROMManager.cpp
//=============================================================================

#include "EEPROMManager.hpp"

void EEPROMManager::initialize() {
    EEPROM.begin(EEPROM_SIZE);
}

void EEPROMManager::speichereWlanDaten(const String &ssid, const String &password) {
    EEPROM.begin(EEPROM_SIZE);

    // Speichere die SSID
    for (size_t i = 0; i < ssid.length(); ++i) {
        EEPROM.write(SSID_ADDR + i, ssid[i]);
    }
    EEPROM.write(SSID_ADDR + ssid.length(), '\0'); // Füge ein Nullzeichen hinzu

    // Speichere das Passwort
    for (size_t i = 0; i < password.length(); ++i) {
        EEPROM.write(PASSWORD_ADDR + i, password[i]);
    }
    EEPROM.write(PASSWORD_ADDR + password.length(), '\0'); // Füge ein Nullzeichen hinzu

    Serial.println("[EEPROM][SAVE] " + ssid + ":" + password);
    EEPROM.commit();
}

String EEPROMManager::leseWlanSSID() {
    String ssid = "";
    char ch;
    for (size_t i = 0; i < 32; ++i) { // Gehe durch die ersten 32 Bytes
        ch = EEPROM.read(SSID_ADDR + i);
        if (ch == '\0') {
            break;
        }
        ssid += ch;
    }
    return ssid;
}

String EEPROMManager::leseWlanPasswort() {
    String password = "";
    char ch;
    for (size_t i = 0; i < 32; ++i) { // Gehe durch die nächsten 32 Bytes
        ch = EEPROM.read(PASSWORD_ADDR + i);
        if (ch == '\0') {
            break;
        }
        password += ch;
    }
    return password;
}


//=============================================================================
// End of File
//=============================================================================