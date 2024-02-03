//=============================================================================
//  InterfaceManager
//-----------------------------------------------------------------------------
//  for:    chickenCoop
//  author: Joe Heumer
//  create: 30 January 2024
//  file:   InterfaceManager.cpp
//=============================================================================

#include "InterfaceManager.hpp"
#include <TimeLib.h>

void InterfaceManager::initialize(void) {
    IEngineLeft.setOutput();
    IEngineRight.setOutput();
    IEngineLeft.setOff();
    IEngineRight.setOff();

    this->setEngine(EEPROMManager::leseEngineDirection());

    this->_time1engine = EEPROMManager::getTime1engine();
    this->_time1limit= EEPROMManager::getTime1limit();
    this->_time1signal= EEPROMManager::getTime1signal();
    this->_time1hour= EEPROMManager::getTime1hour();
    this->_time1min= EEPROMManager::getTime1min();

    this->_time2engine = EEPROMManager::getTime2engine();
    this->_time2limit= EEPROMManager::getTime2limit();
    this->_time2signal= EEPROMManager::getTime2signal();
    this->_time2hour= EEPROMManager::getTime2hour();
    this->_time2min= EEPROMManager::getTime2min();

    ILedGreen.setOutput();
    ILedOrange.setOutput();
    ILedRed.setOutput();

    ILedGreen.setOff();
    ILedOrange.setOff();
    ILedRed.setOff();

    ILimitUp.setInput();
    ILimitDown.setInput();
    ILightSensor.setInput();
}

void InterfaceManager::toggleEngineLeft(void) {
    if (IEngineLeft.status()) this->offEngineLeft();
    else this->onEngineLeft();
}

void InterfaceManager::toggleEngineRight(void) {
    if (IEngineRight.status()) this->offEngineRight();
    else this->onEngineRight();
}

void InterfaceManager::onEngineLeft(void) {
    Serial.println("[INTERFACE][ENGI] Left Engines on");
    IEngineRight.setOff();
    IEngineLeft.setOn();
}
void InterfaceManager::onEngineRight(void) {
    Serial.println("[INTERFACE][ENGI] Right Engines on");
    IEngineLeft.setOff();
    IEngineRight.setOn();
}

void InterfaceManager::offEngineLeft(void) {
    if (IEngineLeft.status()) {
        Serial.println("[INTERFACE][ENGI] Left Engines off");
        IEngineLeft.setOff();
    }

}
void InterfaceManager::offEngineRight(void) {
    if (IEngineRight.status()) {
        Serial.println("[INTERFACE][ENGI] Right Engines off");
        IEngineRight.setOff();
    }
}

void InterfaceManager::offEngines(void) {
    Serial.println("[INTERFACE][ENGI] Both Engines off");
    IEngineLeft.setOff();
    IEngineRight.setOff();
}

void InterfaceManager::setEngine(bool direction) {
    this->_direction = direction;
    IEngineLeft.setOff();
    IEngineRight.setOff();
    
    if (direction) {
        Serial.println("[INTERFACE][ENGI] M1 = Engine Left");
        Serial.println("[INTERFACE][ENGI] M2 = Engine Right");
        IEngineLeft._pin = MotorLinks;
        IEngineRight._pin = MotorRechts;
        EEPROMManager::speichereEngineDirection(direction);
    }
    else {
        Serial.println("[INTERFACE][ENGI] M1 = Engine Right");
        Serial.println("[INTERFACE][ENGI] M2 = Engine Left");
        IEngineLeft._pin = MotorRechts;
        IEngineRight._pin = MotorLinks;    
        EEPROMManager::speichereEngineDirection(direction);    
    }
}

void InterfaceManager::setTime1(bool engine, bool limit, bool signal, int hour, int min) {
    if (engine) 
        Serial.println("[INTERFACE][TIME1] ENGINE = Right");
    else 
        Serial.println("[INTERFACE][TIME1] ENGINE = Left");
    if (limit) 
        Serial.println("[INTERFACE][TIME1] LIMIT = Down");
    else 
        Serial.println("[INTERFACE][TIME1] LIMIT = Up");
    if (signal) 
        Serial.println("[INTERFACE][TIME1] Signal = HIGH");
    else 
        Serial.println("[INTERFACE][TIME1] Signal = LOW");
    Serial.printf("[INTERFACE][TIME1] %d:%d\n", hour, min);
    this->_time1engine = engine;
    this->_time1limit = limit;
    this->_time1hour = hour;
    this->_time1min = min;
    this->_time1signal = signal;

    EEPROMManager::setTime1(engine, limit, signal, hour, min);
}

void InterfaceManager::setTime2(bool engine, bool limit, bool signal, int hour, int min) {
    if (engine) 
        Serial.println("[INTERFACE][TIME2] ENGINE = Right");
    else 
        Serial.println("[INTERFACE][TIME2] ENGINE = Left");
    if (limit) 
        Serial.println("[INTERFACE][TIME2] LIMIT = Down");
    else 
        Serial.println("[INTERFACE][TIME2] LIMIT = Up");
    if (signal) 
        Serial.println("[INTERFACE][TIME2] Signal = HIGH");
    else 
        Serial.println("[INTERFACE][TIME2] Signal = LOW");
    Serial.printf("[INTERFACE][TIME2] %d:%d\n", hour, min);
    this->_time2engine = engine;
    this->_time2limit = limit;
    this->_time2hour = hour;
    this->_time2min = min;
    this->_time2signal = signal;

    EEPROMManager::setTime2(engine, limit, signal, hour, min);
}

unsigned long previousCheckTime1 = 0xFFFFFFF; // Variable für die Zeit der letzten Überprüfung von Bedingung 1
unsigned long previousCheckTime2 = 0xFFFFFFF; // Variable für die Zeit der letzten Überprüfung von Bedingung 2
const unsigned long checkInterval = 90000; // Überprüfungsintervall in Millisekunden (1.5 Minuten)

void InterfaceManager::loop() {
    unsigned long currentMillis = millis(); // Aktuelle Zeit in Millisekunden
    bool limit1Reached = (_time1limit?ILimitDown.status():ILimitUp.status()) == _time1signal;
    bool limit2Reached = (_time2limit?ILimitDown.status():ILimitUp.status()) == _time2signal;

    if ((IEngineLeft.status() || IEngineRight.status()) && millis()%1000>500) ILedOrange.setOn();
    else ILedOrange.setOff();

    // // Überprüfung für Bedingung 1
    if (_time1hour == hour() && _time1min == minute() && !(limit1Reached) && currentMillis - previousCheckTime1 >= checkInterval){
        Serial.println("[INTERFACE][TIME2] Start Time 1");
        if (!_time1engine) this->onEngineLeft();
        else this->onEngineRight();
        previousCheckTime1 = currentMillis; // Aktualisiere die Zeit der letzten Überprüfung für Bedingung 1
    }
    else if (limit1Reached) {
        if (!_time1engine) this->offEngineLeft();
        else this->offEngineRight();
    }

    // // Überprüfung für Bedingung 2
    if (_time2hour == hour() && _time2min == minute() && !(limit2Reached) && currentMillis - previousCheckTime2 >= checkInterval){
        Serial.println("[INTERFACE][TIME2] Start Time 2");
        if (!_time2engine) this->onEngineLeft();
        else this->onEngineRight();
        previousCheckTime2 = currentMillis; // Aktualisiere die Zeit der letzten Überprüfung für Bedingung 2
    }
    else if (limit2Reached) {
        if (!_time2engine) this->offEngineLeft();
        else this->offEngineRight();
    }
}

interface IEngineLeft(MotorLinks);
interface IEngineRight(MotorRechts);
interface ILedGreen(LEDGreen);
interface ILedOrange(LEDOrange);
interface ILedRed(LEDRed);
interface ILimitUp(EndlageOben);
interface ILimitDown(EndlageUnten);
interface ILightSensor(Lichtsensor);

InterfaceManager IManager;




//=============================================================================
// End of File
//=============================================================================