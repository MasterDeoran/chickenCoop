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
#include "EEPROMManager.hpp"

class interface {
    //--------------------------- Methods -----------------------------------------
    public:
        interface(unsigned char pin) : _pin(pin) {};
        int status() { return digitalRead(_pin); }
        void setInput() { pinMode(this->_pin, INPUT_PULLUP); }
        void setOutput() { pinMode(this->_pin, OUTPUT); }
        void setOn() { digitalWrite(this->_pin, HIGH); }
        void setOff() { digitalWrite(this->_pin, LOW); }
        void setToggle() { digitalWrite(this->_pin, !this->status()); }
    private:

    //--------------------------- Variables -----------------------------------------
    public:
        unsigned char _pin;
    private:
        

};
//-----------------------------------------------------------------------------
// Class
//-----------------------------------------------------------------------------

class InterfaceManager {
    //--------------------------- Methods -----------------------------------------
    public:
        InterfaceManager() {};
        void initialize(void);
        // FALSE: left:M1 right:M2, TRUE left:M2 right:M1
        void setEngine(bool direction);
        void onEngineLeft(void);
        void offEngineLeft(void);
        void onEngineRight(void);
        void offEngineRight(void);
        void offEngines(void);

        void setTime1(bool engine, bool limit, bool signal, int hour, int min);
        void setTime2(bool engine, bool limit, bool signal, int hour, int min);

        void loop();

    private:

    //--------------------------- Variables -----------------------------------------
    public:
        bool _direction;
        
        bool _time1engine;
        bool _time1limit;
        bool _time1signal;
        int _time1hour;
        int _time1min;
        bool _time2engine;
        bool _time2limit;
        bool _time2signal;
        int _time2hour;
        int _time2min;

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