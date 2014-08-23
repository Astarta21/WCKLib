/*
  wckLib.h - Library for using Robobuilder wck servos.
  Created by Nuria Perez, August 21 2014.
  Released into the public domain.
*/

#include "Arduino.h"
#include "WCKLib.h"


HardwareSerial _serial = Serial;

// Inicializacion de los puertos indicados
WCKLib::WCKLib()
{
}

int WCKLib::positionMove(int id, int torq, int pos, HardwareSerial serial){
    int posi = 0;
    int tmp1 = (torq << 5) | id;
    int tmp2 = pos; 
    int checksum = (tmp1 ^ tmp2) & 0x7f;

    serial.write(0xff); // Header
    serial.write(tmp1); // Data1: Torq : 0(Max)~4(Min), ID : 0~30
    serial.write(tmp2); // Target position
    serial.write(checksum); //Checsum: (Data1 X OR Target position) AND 0x7F
 
    //first byte: Load
    if (serial.available() > 0) {
        //read the incoming byte:
        int load = serial.read();
    }
    //second byte: position
    if (serial.available() > 0) {
        //read the incoming byte:
        posi = serial.read();
  }
  return posi; 

}

void WCKLib::synchronizedPositionMove(){
  //to do
}

int WCKLib::statusRead(int id, int port){
  int pos = 0;
  
  int tmp1 = 5 | id;
  int tmp2 = 0x00;
  int checksum = (tmp1 ^ tmp2) & 0x7f; 
  Serial.write(0xff); // Header
  Serial.write(tmp1); // Data1: Mode:5,ID:0~30
  Serial.write(tmp2); // Arbitrary value
  Serial.write(checksum); //Checsum: (Data1 X OR Target position) AND 0x7F 
  // first byte: Load
  if (Serial.available() > 0) {
    // read the incoming byte:
    int load = Serial.read();
  }
  // second byte: position
  if (Serial.available() > 0) {
    // read the incoming byte:
    pos = Serial.read();
  }
  return pos;
}  

int WCKLib::pasiveWck(int id, int port){
  int pos = 0;
  
  int tmp1 = 6 | id;
  int tmp2 = 0x10;
  int checksum = (tmp1 ^ tmp2) & 0x7f; 
  Serial.write(0xff); // Header
  Serial.write(tmp1); // Data1: Mode:5,ID:0~30
  Serial.write(tmp2); // Arbitrary value
  Serial.write(checksum); //Checsum: (Data1 X OR Target position) AND 0x7F 
  // first byte: Load
  if (Serial.available() > 0) {
    // read the incoming byte:
    int load = Serial.read();
  }
  // second byte: position
  if (Serial.available() > 0) {
    // read the incoming byte:
    pos = Serial.read();
  }
  
  return pos;
}