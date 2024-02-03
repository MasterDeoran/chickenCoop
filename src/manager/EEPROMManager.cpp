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
    //EEPROM.begin(EEPROM_SIZE);

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

String EEPROMManager::leseWlanPassword() {
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

void EEPROMManager::speichereEngineDirection(bool direction) {
    EEPROM.write(ENGINE_ADDR, static_cast<byte>(direction));
    EEPROM.commit();
}

bool EEPROMManager::leseEngineDirection() {
    byte value = EEPROM.read(ENGINE_ADDR);
    return static_cast<bool>(value);
}

void EEPROMManager::setTime1(bool engine, bool limit, bool signal, int hour, int min) {
    EEPROM.write(ENGINE_ADDR_1, static_cast<byte>(engine));
    EEPROM.write(LIMIT_ADDR_1, static_cast<byte>(limit));
    EEPROM.write(SIGNAL_ADDR_1, static_cast<byte>(signal));
    EEPROM.write(HOUR_ADDR_1, hour);
    EEPROM.write(MIN_ADDR_1, min);
    EEPROM.commit();
}

bool EEPROMManager::getTime1engine() {
    byte value = EEPROM.read(ENGINE_ADDR_1);
    return (value == 1) ? true : false;
}

bool EEPROMManager::getTime1limit() {
    byte value = EEPROM.read(LIMIT_ADDR_1);
    return (value == 1) ? true : false;
}

bool EEPROMManager::getTime1signal() {
    byte value = EEPROM.read(SIGNAL_ADDR_1);
    return (value == 1) ? true : false;
}

int EEPROMManager::getTime1hour() {
    int value = EEPROM.read(HOUR_ADDR_1);
    return (value >= 0 && value <= 23) ? value : 0;
}

int EEPROMManager::getTime1min() {
    int value = EEPROM.read(MIN_ADDR_1);
    return (value >= 0 && value <= 59) ? value : 0;
}

void EEPROMManager::setTime2(bool engine, bool limit, bool signal, int hour, int min) {
    EEPROM.write(ENGINE_ADDR_2, static_cast<byte>(engine));
    EEPROM.write(LIMIT_ADDR_2, static_cast<byte>(limit));
    EEPROM.write(SIGNAL_ADDR_2, static_cast<byte>(signal));
    EEPROM.write(HOUR_ADDR_2, hour);
    EEPROM.write(MIN_ADDR_2, min);
    EEPROM.commit();
}

bool EEPROMManager::getTime2engine() {
    byte value = EEPROM.read(ENGINE_ADDR_2);
    return (value == 1) ? true : false;
}

bool EEPROMManager::getTime2limit() {
    byte value = EEPROM.read(LIMIT_ADDR_2);
    return (value == 1) ? true : false;
}

bool EEPROMManager::getTime2signal() {
    byte value = EEPROM.read(SIGNAL_ADDR_2);
    return (value == 1) ? true : false;
}

int EEPROMManager::getTime2hour() {
    int value = EEPROM.read(HOUR_ADDR_2);
    return (value >= 0 && value <= 23) ? value : 0;
}

int EEPROMManager::getTime2min() {
    int value = EEPROM.read(MIN_ADDR_2);
    return (value >= 0 && value <= 59) ? value : 0;
}

//=============================================================================
// End of File
//=============================================================================