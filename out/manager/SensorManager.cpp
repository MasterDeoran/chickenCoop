//=============================================================================
//  SensorManager
//-----------------------------------------------------------------------------
//  for:    chickenCoop
//  author: Joe Heumer
//  create: 13 January 2024
//  file:   SensorManager.cpp
//=============================================================================

#include "SensorManager.hpp"

void SensorManager::initialize() {
    pinMode(3, INPUT);  
}

void SensorManager::loop() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        this->readSensorValue();
    }
}

void SensorManager::readSensorValue() {
    int sensorValue = digitalRead(3);
    // Verarbeiten des Sensorwertes
    Serial.print("Sensorwert: " + String(sensorValue) + "\n");
}

SensorManager Sensor(10);


//=============================================================================
// End of File
//=============================================================================