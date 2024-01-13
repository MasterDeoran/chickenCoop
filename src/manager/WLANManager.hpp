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




//-----------------------------------------------------------------------------
// Class
//-----------------------------------------------------------------------------

class WLANManager {
    //--------------------------- Methods -----------------------------------------
    public:
        WLANManager();
        WLANManager(const char* ssid, const char* password);
        void verbindeMitWLAN();
        bool istWLANVerbunden();
        String getWifiMac();
        String getSSID();
        String getIPAdress();
        wl_status_t status();

        void setSSID(String ssid);
        void setPassword(String password);
    private:
        String getPassword();
    //--------------------------- Variables -----------------------------------------
    public:
    private:
        String _ssid = "\0";
        String _password = "\0";

};

extern WLANManager wlan;

#endif

//=============================================================================
// End of File
//=============================================================================