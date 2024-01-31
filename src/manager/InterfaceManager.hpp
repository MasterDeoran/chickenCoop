//=============================================================================
//  InterfaceManager Header
//-----------------------------------------------------------------------------
//  for:    firmware-standalone
//  author: Joe Heumer
//  create: 30 January 2024
//  file:   InterfaceManager.hpp
//=============================================================================

#ifndef __INTERFACEMANAGER_H__
#define __INTERFACEMANAGER_H__

#define EndlageOben D1
#define EndlageUnten D2
#define Lichtsensor D3
#define LEDGreen D4
#define MotorLinks D5
#define MotorRechts D6
#define LEDRed D7
#define LEDOrange D8

#include <Arduino.h>

class interface {
    //--------------------------- Methods -----------------------------------------
    public:
        interface(unsigned char pin) : _pin(pin) {};
        int status() { return digitalRead(_pin); }
        void setInput() { pinMode(this->_pin, INPUT_PULLUP); }
        void setOutput() { pinMode(this->_pin, OUTPUT); }
        void setOn() { digitalWrite(this->_pin, HIGH); }
        void setOff() { digitalWrite(this->_pin, LOW); }
    private:

    //--------------------------- Variables -----------------------------------------
    public:
    private:
        unsigned char _pin;

};
//-----------------------------------------------------------------------------
// Class
//-----------------------------------------------------------------------------

class InterfaceManager {
    //--------------------------- Methods -----------------------------------------
    public:
        InterfaceManager() {};
        void initialize(void);
    private:

    //--------------------------- Variables -----------------------------------------
    public:
    private:

};

extern interface IEngineLeft;
extern interface IEngineRight;
extern interface ILedGreen;
extern interface ILedOrange;
extern interface ILedRed;
extern interface ILimitUp;
extern interface ILimitDown;
extern interface ILightSensor;

extern InterfaceManager IManager;

#endif

//=============================================================================
// End of File
//=============================================================================