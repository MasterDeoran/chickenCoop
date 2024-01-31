//=============================================================================
//  WebsiteManager
//-----------------------------------------------------------------------------
//  for:    EMS-standalone
//  author: Joe Heumer
//  create: 01 December 2023
//  file:   WebsiteManager.cpp
//=============================================================================

#include "WebsiteManager.hpp"

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <AsyncTCP.h>
#endif

#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <TimeLib.h>


#ifdef ESP32
    //WebServer server(SERVER_PORT);
    //OTAUpdater otaUpdater(server);
#else
    //ESP8266WebServer server(SERVER_PORT); // Port 80 für den Webserver  
    AsyncWebServer server(SERVER_PORT);
    //AsyncWebServer server(SERVER_PORT);
    //AsyncWebSocket ws("/ws");
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

// void WebsiteManager::onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
//              void *arg, uint8_t *data, size_t len) {
//     switch (type) {
//       case WS_EVT_CONNECT:
//         Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
//         break;
//       case WS_EVT_DISCONNECT:
//         Serial.printf("WebSocket client #%u disconnected\n", client->id());
//         break;
//       case WS_EVT_DATA:
//         handleWebSocketMessage(arg, data, len);
//         break;
//       case WS_EVT_PONG:
//       case WS_EVT_ERROR:
//         break;
//   }
// }

// void WebsiteManager::notifyClients() {
//   ws.textAll(String(ledState));
// }

// void WebsiteManager::handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
//   AwsFrameInfo *info = (AwsFrameInfo*)arg;
//   if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
//     data[len] = 0;
//     if (strcmp((char*)data, "toggle") == 0) {
//       ledState = !ledState;
//       notifyClients();
//     }
//   }
// }

// void WebsiteManager::initWebSocket() {
//   //ws.onEvent(onEvent);
//   server.addHandler(&ws);
// }

void WebsiteManager::websiteInit() {

    //initWebSocket(&server);
    // server.on("/", handleRootStatic);

    server.on("/", HTTP_GET, handleRootStatic);
        //request->send_P(200, "text/html", index_html, processor);
    server.on("/config", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html", config_html);
    });
    server.on("/setCTime", HTTP_GET, handleSetCTimeStatic);
    server.on("/reset", HTTP_GET, handleRestartStatic);
    AsyncElegantOTA.begin(&server);    // Start AsyncElegantOTA
    //server.begin();
    server.begin();
    Serial.println("HTTP server started");


    
    // server.on("/speichern", handleWlanSaveStatic);
    // server.on("/load", handleStartStatic);
    // server.on("/update", HTTP_POST, []() {
    //     server.sendHeader("Connection", "close");
    //     server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    //     ESP.restart();
    //     }, []() { 
    //         #ifdef ESP32 
    //             otaUpdater.handleFirmwareUpload(); 
    //         #endif;
    // });

    // server.begin();
}

bool WebsiteManager::isInitialize() {
    return this->rootPage > 0;
}

void WebsiteManager::serverBegin() {
    server.begin();
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

//---------------------------------------------------------------------------------------------------------------------
//  ROOT
//---------------------------------------------------------------------------------------------------------------------

void WebsiteManager::handleRootStatic(AsyncWebServerRequest *request) {
    if (instance) {
        instance->handleRoot(request);
    }
}

void WebsiteManager::handleRoot(AsyncWebServerRequest *request)
{
    Serial.println("[Website][Root] Neuer Serveraufruf!");
    String html;
    html = index_html;
    // switch (this->rootPage) {
    //     case 0: html = index_html; break;
    //     case 1: html = index_html; break;
    // }
    Serial.println("[Website][Root] Call Time");
    String time = hour() < 10 ? "0" + String(hour()) : String(hour());
    time += ":";
    time += minute() < 10 ? "0" + String(minute()) : String(minute());

    Serial.println("[Website][Root] Call Engine");
    String engine = "Aus";
    if (IEngineLeft.status()) engine = "Linksdrehend";
    if (IEngineRight.status()) engine = "Rechtsdrehend";

    Serial.println("[Website][Root] HTML Replaces");
    html.replace("%s2%", wlan.getSSID());
    html.replace("%s3%", wlan.getIPAdress());
    html.replace("%%TIME%%", time);
    html.replace("%%ENGINE%%", engine);
    html.replace("%%ENDUP%%", ILimitUp.status()?"Nicht erreicht":"Erreicht");
    html.replace("%%ENDDOWN%%", ILimitDown.status()?"Nicht erreicht":"Erreicht");
    html.replace("%%LIGHT%%", ILightSensor.status()?"Aktiv":"Inaktiv");
    html.replace("%%WIFI%%", wlan.istWLANVerbunden()?"connected":"disconnected");

    //server.send(200, "text/html", html);
    Serial.println("[Website][Root] Send Site");
    request->send(200, "text/html", html);
    
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
    //this->handleRoot();
}

void WebsiteManager::handleWlanSave()
{
    // String ssid = AsyncWebServer.arg("ssid");
    // String password = server.arg("password");

    // // Hier sollten die Daten im EEPROM gespeichert werden

    // Serial.print("SSID: " + ssid + "\n");
    // Serial.print("PW:   " + password + "\n");

    // wlan.setSSID(ssid);
    // wlan.setPassword(password);

    // //EEPROMManager::speichereWlanDaten(ssid, password);

    // this->rootPage = 1;
    // this->handleRoot();
    // server.send(200, "text/plain", "Einstellungen gespeichert. Neustart...");
    // Neustart und Verbindung mit den neuen Daten
}

void WebsiteManager::handleSetCTimeStatic(AsyncWebServerRequest *request) {
    if (instance) {
        instance->handleSetCTime(request);
    }
}

void WebsiteManager::handleSetCTime(AsyncWebServerRequest *request) {
    int paramsNr = request->params();
    int hour = 0, min = 0;

    for(int i=0; i<paramsNr; i++){
        AsyncWebParameter* p = request->getParam(i);
        if(p->name() == "hour"){
            hour = p->value().toInt();
        } else if(p->name() == "min"){
            min = p->value().toInt();
        }
    }   
    setTime(hour, min, 0, day(), month(), year());
    String message = "<html><head><meta charset='utf-8' http-equiv='refresh' content='5;url=/'></head><body>Zeit gesetzt zu: ";
    message += hour;
    message += ":";
    message += min;
    message += "<br>Gehe zurück zur Startseite in 5 Sekunden...</body></html>";
    request->send(200, "text/html", message); 
}

void WebsiteManager::handleFirmwareUpdate() {

}

//---------------------------------------------------------------------------------------------------------------------
//  Restart
//---------------------------------------------------------------------------------------------------------------------

void WebsiteManager::handleRestartStatic(AsyncWebServerRequest *request) {
    if (instance) {
        instance->handleRestart(request);
    }
}
void WebsiteManager::handleRestart(AsyncWebServerRequest *request) {
    ESP.restart();
}

void WebsiteManager::loop() {
    AsyncElegantOTA.loop();
    //ws.cleanupClients();
    //server.handleClient();
}

WebsiteManager* WebsiteManager::getInstance() {
    return instance;
}

WebsiteManager website;

//=============================================================================
// End of File
//=============================================================================


