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
    static String leseWlanPassword();
    static void speichereEngineDirection(bool engineDirection);
    static bool leseEngineDirection();

    static void setTime1(bool engine, bool limit, bool signal, int hour, int min);
    static bool getTime1engine();
    static bool getTime1limit();
    static bool getTime1signal();
    static int getTime1hour();
    static int getTime1min();

    static void setTime2(bool engine, bool limit, bool signal, int hour, int min);
    static bool getTime2engine();
    static bool getTime2limit();
    static bool getTime2signal();
    static int getTime2hour();
    static int getTime2min();

private:
    static const int EEPROM_SIZE = 512;
    static const int SSID_ADDR = 0;
    static const int PASSWORD_ADDR = 32;
    static const int ENGINE_ADDR = 64;
    static const int ENGINE_ADDR_1 = 65;
    static const int LIMIT_ADDR_1 = 66;
    static const int SIGNAL_ADDR_1 = 67;
    static const int HOUR_ADDR_1 = 68;
    static const int MIN_ADDR_1 = 69;

    static const int ENGINE_ADDR_2 = 70;
    static const int LIMIT_ADDR_2 = 71;
    static const int SIGNAL_ADDR_2 = 72;
    static const int HOUR_ADDR_2 = 73;
    static const int MIN_ADDR_2 = 74;
};


#endif

//=============================================================================
// End of File
//=============================================================================