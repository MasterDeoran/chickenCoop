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
    this->websiteInit();
}

void WebsiteManager::websiteInit() {

    //initWebSocket(&server);
    // server.on("/", handleRootStatic);

    server.on("/", HTTP_GET, handleRootStatic);
        //request->send_P(200, "text/html", index_html, processor);
    server.on("/config", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html", configMenu_html);
    });
    server.on("/cw", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html", configWLAN_html);
    });
    server.on("/co", HTTP_GET, handleOutputStatic);
    server.on("/cc1", HTTP_GET, handleControl1Static);
    server.on("/cc2", HTTP_GET, handleControl2Static);
    server.on("/ct", HTTP_GET, handleTimeStatic);

    
    server.on("/action", HTTP_GET, handleActionStatic);
    server.on("/setCTime", HTTP_GET, handleSetCTimeStatic);
    server.on("/reset", HTTP_GET, handleRestartStatic);

    server.on("/setE1", HTTP_GET, handleSetE1Static);
    server.on("/setE1w", HTTP_GET, handleSetE1wStatic);
    server.on("/setE2", HTTP_GET, handleSetE2Static);
    server.on("/setE2w", HTTP_GET, handleSetE2wStatic);
    server.on("/setL1", HTTP_GET, handleSetL1Static);
    server.on("/setL2", HTTP_GET, handleSetL2Static);
    server.on("/setL3", HTTP_GET, handleSetL3Static);

    server.on("/saveWifi", HTTP_GET, handleSetWifiStatic);
    server.on("/saveOutput", HTTP_GET, handleSetOutputStatic);
    server.on("/saveTime1", HTTP_GET, handleSetTime1Static);
    server.on("/saveTime2", HTTP_GET, handleSetTime2Static);

    AsyncElegantOTA.begin(&server);    // Start AsyncElegantOTA
    server.begin();
    Serial.println("HTTP server started");

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
    html.replace("%%ENDUP%%", ILimitUp.status()?"HIGH-Pegel":"LOW-Pegel");
    html.replace("%%ENDDOWN%%", ILimitDown.status()?"HIGH-Pegel":"LOW-Pegel");
    html.replace("%%LIGHT%%", ILightSensor.status()?"Aktiv":"Inaktiv");
    html.replace("%%WIFI%%", wlan.istWLANVerbunden()?"connected":"disconnected");

    //server.send(200, "text/html", html);
    Serial.println("[Website][Root] Send Site");
    request->send(200, "text/html", html);
    
}

//---------------------------------------------------------------------------------------------------------------------
//  Action
//---------------------------------------------------------------------------------------------------------------------

void WebsiteManager::handleActionStatic(AsyncWebServerRequest *request) {
    if (instance) {
        instance->handleAction(request);
    }
}

void WebsiteManager::handleAction(AsyncWebServerRequest *request)
{
    Serial.println("[Website][ACTI] Neuer Serveraufruf!");
    String html;
    html = action_html;

    Serial.println("[Website][ACTI] Call Time");
    String time = hour() < 10 ? "0" + String(hour()) : String(hour());
    time += ":";
    time += minute() < 10 ? "0" + String(minute()) : String(minute());

    Serial.println("[Website][ACTI] Call Engine");
    String engine = "Aus";
    if (IEngineLeft.status()) engine = "Linksdrehend";
    if (IEngineRight.status()) engine = "Rechtsdrehend";

    Serial.println("[Website][ACTI] HTML Replaces");
    html.replace("%%STATUSE1%%", IEngineLeft.status()?"ON":"OFF");
    html.replace("%%STATUSE2%%", IEngineRight.status()?"ON":"OFF");
    html.replace("%%STATUSL1%%", ILedGreen.status()?"ON":"OFF");
    html.replace("%%STATUSL2%%", ILedOrange.status()?"ON":"OFF");
    html.replace("%%STATUSL3%%", ILedRed.status()?"ON":"OFF");

    //server.send(200, "text/html", html);
    Serial.println("[Website][ACTI] Send Site");
    request->send(200, "text/html", html);
    
}

//---------------------------------------------------------------------------------------------------------------------
//  Output
//---------------------------------------------------------------------------------------------------------------------

void WebsiteManager::handleOutputStatic(AsyncWebServerRequest *request) {
    if (instance) {
        instance->handleOutput(request);
    }
}

void WebsiteManager::handleOutput(AsyncWebServerRequest *request)
{
    String html;
    html = configOutput_html;

    Serial.println("[Website][OUTP] HTML Replaces");
    html.replace("%%M1%%", IManager._direction?"Rechtslauf":"Linkslauf");
    html.replace("%%M2%%", IManager._direction?"Linkslauf":"Rechtslauf");
    html.replace("%%STATUSE1%%", IEngineLeft.status()?"ON":"OFF");
    html.replace("%%STATUSE2%%", IEngineRight.status()?"ON":"OFF");

    Serial.println("[Website][OUTP] Send Site");
    request->send(200, "text/html", html);
    
}

//---------------------------------------------------------------------------------------------------------------------
//  Output
//---------------------------------------------------------------------------------------------------------------------

void WebsiteManager::handleControl1Static(AsyncWebServerRequest *request) {
    if (instance) {
        instance->handleControl1(request);
    }
}

void WebsiteManager::handleControl1(AsyncWebServerRequest *request)
{
    String html;
    html = configControl1_html;

    Serial.println("[Website][CONT] HTML Replaces");
    html.replace("%%h1%%", ("value='" + String(IManager._time1hour) + "'"));
    html.replace("%%m1%%", ("value='" + String(IManager._time1min) + "'"));
    html.replace("%%s11%%", IManager._time1engine?"":"selected");
    html.replace("%%s12%%", IManager._time1engine?"selected":"");
    html.replace("%%s13%%", IManager._time1limit?"":"selected");
    html.replace("%%s14%%", IManager._time1limit?"selected":"");
    html.replace("%%s15%%", IManager._time1signal?"":"selected");
    html.replace("%%s16%%", IManager._time1signal?"selected":"");

    Serial.println("[Website][CONT] Send Site");
    request->send(200, "text/html", html);
    
}

//---------------------------------------------------------------------------------------------------------------------
//  Output
//---------------------------------------------------------------------------------------------------------------------

void WebsiteManager::handleControl2Static(AsyncWebServerRequest *request) {
    if (instance) {
        instance->handleControl2(request);
    }
}

void WebsiteManager::handleControl2(AsyncWebServerRequest *request)
{
    String html;
    html = configControl2_html;

    Serial.println("[Website][CONT] HTML Replaces");
    html.replace("%%h2%%", ("value='" + String(IManager._time2hour) + "'"));
    html.replace("%%m2%%", ("value='" + String(IManager._time2min) + "'"));
    html.replace("%%s21%%", IManager._time2engine?"":"selected");
    html.replace("%%s22%%", IManager._time2engine?"selected":"");
    html.replace("%%s23%%", IManager._time2limit?"":"selected");
    html.replace("%%s24%%", IManager._time2limit?"selected":"");
    html.replace("%%s25%%", IManager._time2signal?"":"selected");
    html.replace("%%s26%%", IManager._time2signal?"selected":"");

    Serial.println("[Website][CONT] Send Site");
    request->send(200, "text/html", html);
    
}

//---------------------------------------------------------------------------------------------------------------------
//  Tiome
//---------------------------------------------------------------------------------------------------------------------

void WebsiteManager::handleTimeStatic(AsyncWebServerRequest *request) {
    if (instance) {
        instance->handleTime(request);
    }
}

void WebsiteManager::handleTime(AsyncWebServerRequest *request)
{
    String html;
    html = configTime_html;

    Serial.println("[Website][TIME] Call Time");
    String time = hour() < 10 ? "0" + String(hour()) : String(hour());
    time += ":";
    time += minute() < 10 ? "0" + String(minute()) : String(minute());

    Serial.println("[Website][TIME] HTML Replaces");
    html.replace("%%TIME%%", time);

    Serial.println("[Website][TIME] Send Site");
    request->send(200, "text/html", html);
    
}

void WebsiteManager::handleStart()
{

    String ssid = EEPROMManager::leseWlanSSID();
    String password = EEPROMManager::leseWlanPassword();

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

void WebsiteManager::handleSetE1Static(AsyncWebServerRequest *request) {
    if (instance) {
        instance->handleSetE1(request);
    }
}
void WebsiteManager::handleSetE1(AsyncWebServerRequest *request) {
    
    IManager.toggleEngineLeft();
    this->handleAction(request);
}

void WebsiteManager::handleSetE2Static(AsyncWebServerRequest *request) {
    if (instance) {
        instance->handleSetE2(request);
    }
}
void WebsiteManager::handleSetE2(AsyncWebServerRequest *request) {
    IManager.toggleEngineRight();
    this->handleAction(request);
}

void WebsiteManager::handleSetE1wStatic(AsyncWebServerRequest *request) {
    if (instance) {
        instance->handleSetE1w(request);
    }
}
void WebsiteManager::handleSetE1w(AsyncWebServerRequest *request) {
    IManager.toggleEngineLeft();
    this->handleOutput(request);
}

void WebsiteManager::handleSetE2wStatic(AsyncWebServerRequest *request) {
    if (instance) {
        instance->handleSetE2w(request);
    }
}
void WebsiteManager::handleSetE2w(AsyncWebServerRequest *request) {
    IManager.toggleEngineRight();
    this->handleOutput(request);
}

void WebsiteManager::handleSetL1Static(AsyncWebServerRequest *request) {
    if (instance) {
        instance->handleSetL1(request);
    }
}
void WebsiteManager::handleSetL1(AsyncWebServerRequest *request) {
    ILedGreen.setToggle();
    this->handleAction(request);
}

void WebsiteManager::handleSetL2Static(AsyncWebServerRequest *request) {
    if (instance) {
        instance->handleSetL2(request);
    }
}
void WebsiteManager::handleSetL2(AsyncWebServerRequest *request) {
    ILedOrange.setToggle();
    this->handleAction(request);
}

void WebsiteManager::handleSetL3Static(AsyncWebServerRequest *request) {
    if (instance) {
        instance->handleSetL3(request);
    }
}
void WebsiteManager::handleSetL3(AsyncWebServerRequest *request) {
    ILedRed.setToggle();
    this->handleAction(request);
}

//---------------------------------------------------------------------------------------------------------------------
//  Set WIFI
//---------------------------------------------------------------------------------------------------------------------

void WebsiteManager::handleSetWifiStatic(AsyncWebServerRequest *request) {
    if (instance) {
        instance->handleSetWifi(request);
    }
}
void WebsiteManager::handleSetWifi(AsyncWebServerRequest *request) {

    int paramsNr = request->params();
    String ssid, password;

    for(int i=0; i<paramsNr; i++){
        AsyncWebParameter* p = request->getParam(i);
        if(p->name() == "ssid"){
            ssid = p->value();
        } else if(p->name() == "password"){
            password = p->value();
        }
    }   

    // Hier sollten die Daten im EEPROM gespeichert werden

    Serial.print("SSID: " + ssid + "\n");
    Serial.print("PW:   " + password + "\n");

    wlan.setSSID(ssid);
    wlan.setPassword(password);

    EEPROMManager::speichereWlanDaten(wlan.getSSID(), wlan.getPassword());

    wlan.verbinde();
    request->send(200, "text/html", configWLAN_html);
}

//---------------------------------------------------------------------------------------------------------------------
//  Set Output
//---------------------------------------------------------------------------------------------------------------------

void WebsiteManager::handleSetOutputStatic(AsyncWebServerRequest *request) {
    if (instance) {
        instance->handleSetOutput(request);
    }
}
void WebsiteManager::handleSetOutput(AsyncWebServerRequest *request) {
    int paramsNr = request->params();
    String value;

    for(int i=0; i<paramsNr; i++){
        AsyncWebParameter* p = request->getParam(i);
        if(p->name() == "engine1"){
            IManager.setEngine(p->value() == "1"?true:false);
        }
    }   
    handleOutput(request); 
}

//---------------------------------------------------------------------------------------------------------------------
//  Set Time 1
//---------------------------------------------------------------------------------------------------------------------

void WebsiteManager::handleSetTime1Static(AsyncWebServerRequest *request) {
    if (instance) {
        instance->handleSetTime1(request);
    }
}
void WebsiteManager::handleSetTime1(AsyncWebServerRequest *request) {
    int paramsNr = request->params();
    bool engine, limit, signal;
    int hour, min;

    for(int i=0; i<paramsNr; i++){
        AsyncWebParameter* p = request->getParam(i);
        if(p->name() == "engine1")  engine = (p->value() == "1"?true:false);
        else if (p->name() == "limit1") limit = (p->value() == "1"?true:false);
        else if (p->name() == "hour") hour = p->value().toInt();
        else if (p->name() == "min") min = p->value().toInt();
        else if (p->name() == "signal1") signal = (p->value() == "1"?true:false);
    }   
    IManager.setTime1(engine, limit, signal, hour, min);
    
    handleControl1(request); 
}

//---------------------------------------------------------------------------------------------------------------------
//  Set Time 2
//---------------------------------------------------------------------------------------------------------------------

void WebsiteManager::handleSetTime2Static(AsyncWebServerRequest *request) {
    if (instance) {
        instance->handleSetTime2(request);
    }
}
void WebsiteManager::handleSetTime2(AsyncWebServerRequest *request) {
    int paramsNr = request->params();
    bool engine, limit, signal;
    int hour, min;

    for(int i=0; i<paramsNr; i++){
        AsyncWebParameter* p = request->getParam(i);
        if(p->name() == "engine2")  engine = (p->value() == "1"?true:false);
        else if (p->name() == "limit2") limit = (p->value() == "1"?true:false);
        else if (p->name() == "hour") hour = p->value().toInt();
        else if (p->name() == "min") min = p->value().toInt();
        else if (p->name() == "signal2") signal = (p->value() == "1"?true:false);
    }   
    IManager.setTime2(engine, limit, signal, hour, min);
    
    handleControl2(request); 
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