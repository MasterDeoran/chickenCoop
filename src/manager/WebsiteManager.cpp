//=============================================================================
//  WebsiteManager
//-----------------------------------------------------------------------------
//  for:    EMS-standalone
//  author: Joe Heumer
//  create: 01 December 2023
//  file:   WebsiteManager.cpp
//=============================================================================

#include "WebsiteManager.hpp"

#ifdef ESP32
    WebServer server(SERVER_PORT);
#else
    ESP8266WebServer server(SERVER_PORT); // Port 80 für den Webserver  
#endif


WebsiteManager* WebsiteManager::instance = nullptr; // Initialisiere statische Instanz

unsigned long startZeit = 0; // Speichert die Startzeit
const unsigned long timeout = 300000; // 5 Minuten in Millisekunden


WebsiteManager::WebsiteManager() {
    instance = this; // Setze die statische Instanz
}

void WebsiteManager::initialize() {

    this->local_IP = AP_LOCAL_IP;
    this->gateway = AP_GATEWAY;
    this->subnet = AP_SUBNET;
    this->espName = AP_SSID;

    // Konfiguriere den SoftAP-Modus mit der statischen IP
    if (!WiFi.softAPConfig(this->local_IP, this->gateway, this->subnet))
    {
        Serial.println("SoftAP Konfiguration fehlgeschlagen!");
    }

    // Initialisiere das WLAN und den Webserver
    WiFi.softAP(this->espName.c_str());
    this->websiteInit();

    startZeit = millis(); // Initialisiere den Timer beim Start
}

void WebsiteManager::websiteInit() {
    server.on("/", handleRootStatic);
    server.on("/speichern", handleWlanSaveStatic);
    server.on("/load", handleStartStatic);
    server.begin();
}

bool WebsiteManager::isInitialize() {
    return this->rootPage > 0;
}

void WebsiteManager::serverBegin() {
    server.begin();
}

void WebsiteManager::handleRootStatic() {
    if (instance) {
        instance->handleRoot();
    }
}

void WebsiteManager::handleWlanSaveStatic() {
    if (instance) {
        instance->handleWlanSave();
    }
}

void WebsiteManager::handleStartStatic() {
    if (instance) {
        instance->handleStart();
    }
}

void WebsiteManager::handleRoot()
{
    String html;
    switch (this->rootPage) {
        case 0: html = "<html> <meta name='viewport' content='width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no'/> <style> body { text-align: center; background-color: cornflowerblue; } div, input { margin: 5px; } </style> <body> <h1>ESP-Konfiguration</h1> <form action='/load'> <h2>Overview</h2> <div>Version: 1.0</div> <input type='submit' value='ESP Start'> </form> <form action='/speichern'> <h2>WLAN - Settings</h2> <div>SSID</div><input type='text' name='ssid'><br> <div>Password: </div><input type='password' name='password'><br><input type='submit' value='Save'> </form> </body> </html>"; break;
        case 1: html = "<html> <meta name='viewport' content='width=device-width,initial-scale=1,maximum-scale=1,user-scalable=no' /> <style> body { text-align: center; background-color: cornflowerblue; } div, input { margin: 5px; } </style> <body> <h1>ESP Sensorbox</h1> <h2>Overview</h2> <div>Version: 1.0</div> <div>WLAN: %s1%</div> <div>SSID: %s2%</div> <div>IP-Address: %s3%</div> </body> </html>"; break;
    }

    if (this->isInitialize()) {
        html.replace("%s1%", wlan.istWLANVerbunden()?"connected":"disconnected");
        html.replace("%s2%", wlan.getSSID());
        html.replace("%s3%", wlan.getIPAdress());
    }

    server.send(200, "text/html", html);
    Serial.println("Neuer Serveraufruf!");
}

void WebsiteManager::handleStart()
{

    String ssid = EEPROMManager::leseWlanSSID();
    String password = EEPROMManager::leseWlanPasswort();

    Serial.print("SSID: " + ssid + "\n");
    Serial.print("PW:   " + password + "\n");

    wlan.setSSID(ssid);
    wlan.setPassword(password);

    this->rootPage = 1;
    this->handleRoot();
}

void WebsiteManager::handleWlanSave()
{
    String ssid = server.arg("ssid");
    String password = server.arg("password");

    // Hier sollten die Daten im EEPROM gespeichert werden

    Serial.print("SSID: " + ssid + "\n");
    Serial.print("PW:   " + password + "\n");

    wlan.setSSID(ssid);
    wlan.setPassword(password);

    EEPROMManager::speichereWlanDaten(ssid, password);

    this->rootPage = 1;
    this->handleRoot();
    //server.send(200, "text/plain", "Einstellungen gespeichert. Neustart...");
    // Neustart und Verbindung mit den neuen Daten
}

void WebsiteManager::loop() {
    server.handleClient();
}

WebsiteManager* WebsiteManager::getInstance() {
    return instance;
}

WebsiteManager website;

//=============================================================================
// End of File
//=============================================================================


