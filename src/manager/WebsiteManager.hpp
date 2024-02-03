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
// #ifdef ESP32
//     #include <WebServer.h> // Für ESP32
//     #include "../object/OTAUpdater.hpp"
// #else
//     #include <ESP8266WebServer.h> // Für ESP8266
// #endif

#include "WLANManager.hpp"
#include "EEPROMManager.hpp"
#include "InterfaceManager.hpp"
#include "../config.h"
#include "../object/websocket.h"
#include "../object/pages.h"




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
        static void handleRootStatic(AsyncWebServerRequest *request); // Statische Wrapper-Funktionen
        static void handleActionStatic(AsyncWebServerRequest *request); // Statische Wrapper-Funktionen
        static void handleOutputStatic(AsyncWebServerRequest *request); // Statische Wrapper-Funktionen
        static void handleTimeStatic(AsyncWebServerRequest *request); // Statische Wrapper-Funktionen
        static void handleControl1Static(AsyncWebServerRequest *request); // Statische Wrapper-Funktionen
        static void handleControl2Static(AsyncWebServerRequest *request); // Statische Wrapper-Funktionen
        static void handleWlanSaveStatic();
        static void handleStartStatic();
        static void handleSetCTimeStatic(AsyncWebServerRequest *request);

        static void handleRestartStatic(AsyncWebServerRequest *request);
        void handleRoot(AsyncWebServerRequest *request);
        void handleAction(AsyncWebServerRequest *request);
        void handleOutput(AsyncWebServerRequest *request);
        void handleTime(AsyncWebServerRequest *request);
        void handleControl1(AsyncWebServerRequest *request);
        void handleControl2(AsyncWebServerRequest *request);
        void handleWlanSave();
        void handleStart();
        void handleFirmwareUpdate();
        void handleSetCTime(AsyncWebServerRequest *request);
        void handleRestart(AsyncWebServerRequest *request);

        static void handleSetE1Static(AsyncWebServerRequest *request);
        static void handleSetE1wStatic(AsyncWebServerRequest *request);
        static void handleSetE2Static(AsyncWebServerRequest *request);
        static void handleSetE2wStatic(AsyncWebServerRequest *request);
        static void handleSetL1Static(AsyncWebServerRequest *request);
        static void handleSetL2Static(AsyncWebServerRequest *request);
        static void handleSetL3Static(AsyncWebServerRequest *request);
        static void handleSetWifiStatic(AsyncWebServerRequest *request);
        static void handleSetOutputStatic(AsyncWebServerRequest *request);
        static void handleSetTime1Static(AsyncWebServerRequest *request);
        static void handleSetTime2Static(AsyncWebServerRequest *request);
        
        void handleSetE1(AsyncWebServerRequest *request);
        void handleSetE1w(AsyncWebServerRequest *request);
        void handleSetE2(AsyncWebServerRequest *request);
        void handleSetE2w(AsyncWebServerRequest *request);
        void handleSetL1(AsyncWebServerRequest *request);
        void handleSetL2(AsyncWebServerRequest *request);
        void handleSetL3(AsyncWebServerRequest *request);       
        void handleSetWifi(AsyncWebServerRequest *request);  
        void handleSetOutput(AsyncWebServerRequest *request);
        void handleSetTime1(AsyncWebServerRequest *request);
        void handleSetTime2(AsyncWebServerRequest *request);  
        // void initWebSocket(void);
        // static void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
        // void WebsiteManager::notifyClients();
        // void WebsiteManager::handleWebSocketMessage(void *arg, uint8_t *data, size_t len);

    //--------------------------- Variables -----------------------------------------
    public:
    private:
        int rootPage = 0;


};

extern WebsiteManager website;

#endif

//=============================================================================
// End of File
//=============================================================================