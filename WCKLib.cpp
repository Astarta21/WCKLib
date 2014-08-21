/*
  wckLib.h - Library for using Robobuilder wck servos.
  Created by Nuria Perez, August 21 2014.
  Released into the public domain.
*/

#include "Arduino.h"
#include "WCKLib.h"

// Inicializacion de los puertos indicados
WCKLib::WCKLib(int ports[4])
{
    if(ports[0]==1){
        _port0 = true;
        Serial.begin(115200);
    }else{
        _port0=false;
    }
    
    if(ports[1]==1){
        _port1 = true;
        Serial1.begin(115200);
    }else{
        _port1=false;
    }
    
    if(ports[2]==1){
        _port2 = true;
        Serial2.begin(115200);
    }else{
        _port2=false;
    }
    
    if(ports[3]==1){
        _port3 = true;
        Serial3.begin(115200);
    }else{
        _port3=false;
    }
}

int WCKLib::positionMove(int id, int torq, int pos, int port){
  int posi = 0;
  int tmp1 = (torq << 5) | id;
  int tmp2 = pos; 
  int checksum = (tmp1 ^ tmp2) & 0x7f;
  HardwareSerial serial = Serial;
  switch (port) {
    case 0:
        serial = Serial;
        break;
    case 1:
        serial = Serial1;
        break;
    case 2:
        serial = Serial2;
        break;
    case 3:
        serial = Serial3;
        break;
    default: 
      return -1;
  }
  serial.write(0xff); // Header
  serial.write(tmp1); // Data1: Torq : 0(Max)~4(Min), ID : 0~30
  serial.write(tmp2); // Target position
  serial.write(checksum); //Checsum: (Data1 X OR Target position) AND 0x7F
 
 // first byte: Load
  if (serial.available() > 0) {
    // read the incoming byte:
    int load = serial.read();
  }
  // second byte: position
  if (serial.available() > 0) {
    // read the incoming byte:
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