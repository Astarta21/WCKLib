/*
  wckLib.h - Library for using Robobuilder wck servos.
  Created by Nuria Perez, August 21 2014.
  Released into the public domain.
*/
#ifndef WCKLib_h
#define WCKLib_h

#include "Arduino.h"

class WCKLib
{
  public:
    WCKLib();
    int positionMove(int id, int torq, int pos, HardwareSerial serial);
    void synchronizedPositionMove(int lastId, int torq, int pos[], HardwareSerial serial);
    int statusRead(int id, int port, HardwareSerial serial);
    int pasiveWck(int id, int port, HardwareSerial serial);
    int wheelRotation(int id, int direction, int speed, HardwareSerial serial);
    int breakWck(HardwareSerial serial);
    int baudrateSet(int id, int baudrate, HardwareSerial serial);
    int pdGainSet(int id, int pGain, int dGain, HardwareSerial serial);
    int pdGainRead(int id, HardwareSerial serial);
    int iGainSet(int id, int iGain, HardwareSerial serial);
    int iGainReadI(int id, HardwareSerial serial);
    int runtimePdGainSet(int id, int pGain, int dGain, HardwareSerial serial);
    int runtimeIGainSet(int id, int iGain, HardwareSerial serial);
    int idSet(int id, int newId, HardwareSerial serial);
    int speedSet(int id, int speed, int acceleration, HardwareSerial serial);
    int speedRead(int id, HardwareSerial serial);
    int runtimeSpeedSet(int id, int speed, int acceleration, HardwareSerial serial);
};

#endif
