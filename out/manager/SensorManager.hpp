//=============================================================================
//  SensorManager Header
//-----------------------------------------------------------------------------
//  for:    chickenCoop
//  author: Joe Heumer
//  create: 13 January 2024
//  file:   SensorManager.hpp
//=============================================================================

#ifndef __SENSORMANAGER_H__
#define __SENSORMANAGER_H__

#include "Arduino.h"

//-----------------------------------------------------------------------------
// Class
//-----------------------------------------------------------------------------

class SensorManager {
    //--------------------------- Methods -----------------------------------------
    public:
        SensorManager(unsigned long timeInterval) : interval(timeInterval * 1000) {}
        void initialize(void);
        void loop(void);
    private:
        void readSensorValue(void);

    //--------------------------- Variables -----------------------------------------
    public:
    private:
        unsigned long previousMillis = 0;
        unsigned long interval;  // Intervall in Millisekunden

};

extern SensorManager Sensor;

#endif

//=============================================================================
// End of File
//=============================================================================