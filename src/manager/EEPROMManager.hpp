//=============================================================================
//  EEPROM Header
//-----------------------------------------------------------------------------
//  for:    EMS-standalone
//  author: Joe Heumer
//  create: 01 December 2023
//  file:   EEPROM.hpp
//=============================================================================

#ifndef __EEPROM_H__
#define __EEPROM_H__


//-----------------------------------------------------------------------------
// Class
//-----------------------------------------------------------------------------

class EEPROM {
    //--------------------------- Methods -----------------------------------------
    public:
    private:

    //--------------------------- Variables -----------------------------------------
    public:
    private:

};


#endif

//=============================================================================
// End of File
//=============================================================================//=============================================================================
//  EEPROM Header
//-----------------------------------------------------------------------------
//  for:    EMS-standalone
//  author: Joe Heumer
//  create: 01 December 2023
//  file:   EEPROMManager.hpp
//=============================================================================

#ifndef __EEPROMMANAGER_H__
#define __EEPROMMANAGER_H__

#include <Arduino.h>
#include <EEPROM.h>

class EEPROMManager {
public:
    static void initialize();
    static void speichereWlanDaten(const String &ssid, const String &password);
    static String leseWlanSSID();
    static String leseWlanPasswort();

private:
    static const int EEPROM_SIZE = 512;
    static const int SSID_ADDR = 0;
    static const int PASSWORD_ADDR = 32;
};


#endif

//=============================================================================
// End of File
//=============================================================================