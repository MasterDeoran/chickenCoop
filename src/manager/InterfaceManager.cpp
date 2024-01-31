//=============================================================================
//  InterfaceManager
//-----------------------------------------------------------------------------
//  for:    chickenCoop
//  author: Joe Heumer
//  create: 30 January 2024
//  file:   InterfaceManager.cpp
//=============================================================================

#include "InterfaceManager.hpp"

void InterfaceManager::initialize(void) {
    IEngineLeft.setOutput();
    IEngineRight.setOutput();
    IEngineLeft.setOff();
    IEngineRight.setOff();

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