//=============================================================================
//  WebsiteManager Header
//-----------------------------------------------------------------------------
//  for:    EMS-standalone
//  author: Joe Heumer
//  create: 01 December 2023
//  file:   WebsiteManager.hpp
//=============================================================================

#ifndef __WEBSITEMANAGER_H__
#define __WEBSITEMANAGER_H__

#include <Arduino.h>
#ifdef ESP32
    #include <WebServer.h> // Für ESP32
#else
    #include <ESP8266WebServer.h> // Für ESP8266
#endif
#include "WLANManager.hpp"
#include "EEPROMManager.hpp"
#include "../config.h"



//-----------------------------------------------------------------------------
// Class
//-----------------------------------------------------------------------------

class WebsiteManager {
    //--------------------------- Methods -----------------------------------------
    public:
        WebsiteManager();
        void initialize();
        void websiteInit();
        void loop();
        static WebsiteManager* getInstance();
        bool isInitialize();
        void serverBegin();
    private:
        static WebsiteManager* instance; // Statische Instanz für den Zugriff in den Callbacks
        static void handleRootStatic(); // Statische Wrapper-Funktionen
        static void handleWlanSaveStatic();
        static void handleStartStatic();
        void handleRoot();
        void handleWlanSave();
        void handleStart();

    //--------------------------- Variables -----------------------------------------
    public:
    private:
        int rootPage = 0;
        String espName;
        IPAddress local_IP;
        IPAddress gateway;
        IPAddress subnet;

};

extern WebsiteManager website;

#endif

//=============================================================================
// End of File
//=============================================================================