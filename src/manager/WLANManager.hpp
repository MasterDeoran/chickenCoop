//=============================================================================
//  WLANManager Header
//-----------------------------------------------------------------------------
//  for:    test-ESP8266
//  author: Joe Heumer
//  create: 25 October 2023
//  file:   WLANManager.hpp
//=============================================================================

#ifndef __WLANMANAGER_H__
#define __WLANMANAGER_H__

#if defined(ESP32)
    #include <WiFi.h>
#elif defined(ESP8266)
    #include <ESP8266WiFi.h>
#else
    #error "Bitte wählen Sie entweder ESP32 oder ESP8266 als Zielplattform aus!"
#endif

#include "EEPROMManager.hpp"
#include "../config.h"


//-----------------------------------------------------------------------------
// Class
//-----------------------------------------------------------------------------

class WLANManager {
    //--------------------------- Methods -----------------------------------------
    public:
        WLANManager();
        WLANManager(const char* ssid, const char* password);
        void initializeSoftAP(void);
        void openSoftAP(void);
        void closeSoftAP(void);
        void verbinde();
        bool istWLANVerbunden();
        void setOn(void);
        void setOff(void);
        String getWifiMac();
        String getSSID();
        String getPassword();
        String getIPAdress();
        wl_status_t status();

        void setSSID(String ssid);
        void setPassword(String password);
        void update(void);

    enum mwifi_state_t {
        WIFI_STATE_WAITING_FOR_CONNECTION,
        WIFI_STATE_CONNECTED,
        WIFI_STATE_DISCONNECTED,
    };

    private:
        void verbindeMitWLAN();
    //--------------------------- Variables -----------------------------------------
    public:
    private:
        String _ssid = "";
        String _password = "";
        unsigned long _lastConnect = 0;
        unsigned long _wifiInterval = 60000;
        bool _initialize = false;
        bool _enabled = false;
        mwifi_state_t _state = WIFI_STATE_WAITING_FOR_CONNECTION;
        String espName;
        IPAddress local_IP;
        IPAddress gateway;
        IPAddress subnet;

};

extern WLANManager wlan;

#endif

//=============================================================================
// End of File
//=============================================================================