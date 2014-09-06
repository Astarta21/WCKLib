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
};

#endif
