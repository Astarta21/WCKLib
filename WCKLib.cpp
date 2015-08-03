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

void WCKLib::synchronizedPositionMove(int lastId, int torq, int pos[], HardwareSerial serial){
    int tmp1 = (torq << 5) | 31;
    int tmp2 = lastId + 1; 
    int posis = pos[0];
    for(int i = 1; i < lastId; i = i + 1) posis = posis ^ pos[i];
    int checksum = posis & 0x7f;

    serial.write(0xff); // Header
    serial.write(tmp1); // Data1: Torq : 0(Max)~4(Min), 31
    serial.write(tmp2); // Data2: arbitrary value, last ID
    for(int i = 0; i < lastId; i = i + 1) serial.write(pos[i]); // IDx target
    serial.write(checksum); //Checsum: (ID0 XOR ID1... XOR LastID + 3) AND 0x7F
}

int WCKLib::statusRead(int id, int port, HardwareSerial serial){
  int pos = 0;
  
  int tmp1 = (5 << 5) | id;
  int tmp2 = 0x00;
  int checksum = (tmp1 ^ tmp2) & 0x7f; 
  serial.write(0xff); // Header
  serial.write(tmp1); // Data1: Mode:5,ID:0~30
  serial.write(tmp2); // Arbitrary value
  serial.write(checksum); //Checsum: (Data1 X OR Target position) AND 0x7F 
  // first byte: Load
  if (serial.available() > 0) {
    // read the incoming byte:
    int load = serial.read();
  }
  // second byte: position
  if (serial.available() > 0) {
    // read the incoming byte:
    pos = serial.read();
  }
  return pos;
}  

int WCKLib::pasiveWck(int id, int port, HardwareSerial serial){
  int pos = 0;
  
  int tmp1 = (6 << 5) | id;
  int tmp2 = 0x10;
  int checksum = (tmp1 ^ tmp2) & 0x7f; 
  serial.write(0xff); // Header
  serial.write(tmp1); // Data1: Mode:5,ID:0~30
  serial.write(tmp2); // Arbitrary value
  serial.write(checksum); //Checsum: (Data1 X OR Target position) AND 0x7F 
  // first byte: Load
  if (serial.available() > 0) {
    // read the incoming byte:
    int load = Serial.read();
  }
  // second byte: position
  if (serial.available() > 0) {
    // read the incoming byte:
    pos = Serial.read();
  }
  
  return pos;
}

int WCKLib::wheelRotation(int id, int direction, int speed, HardwareSerial serial){
    int pos = 0;
  
  int tmp1 = (6 << 5) | id;
  //direction must be 3 or 4 and speed 0-15
  int tmp2 = (direction << 5)|speed;
  int checksum = (tmp1 ^ tmp2) & 0x7f; 
  serial.write(0xff); // Header
  serial.write(tmp1); // Data1: Mode:6,ID:0~30
  serial.write(tmp2); // Data1: direction, speed
  serial.write(checksum); //Checsum: (Data1 X OR Target position) AND 0x7F 
  // first byte: Load
  if (serial.available() > 0) {
    // read the incoming byte:
    int rotations = Serial.read();
  }
  // second byte: position
  if (serial.available() > 0) {
    // read the incoming byte:
    pos = Serial.read();
  }
  
  return pos;

}

int WCKLib::breakWck(HardwareSerial serial){
  int pos = 0;
  int tmp1 = 0xdf;
  int tmp2 = 0x20;
  int checksum = (tmp1 ^ tmp2) & 0x7f; 
  serial.write(0xff); // Header
  serial.write(tmp1); // Data1: Mode:6,ID:31
  serial.write(tmp2); // Data2: Mode:2, arbitrary value
  serial.write(checksum); //Checsum: (Data1 X OR Target position) AND 0x7F 
  // first byte: Load
  if (serial.available() > 0) {
    // read the incoming byte:
    int rotations = Serial.read();
  }
  // second byte: position
  if (serial.available() > 0) {
    // read the incoming byte:
    pos = Serial.read();
  }
  
  return pos;
}

int WCKLib::baudrateSet(int id, int baudrate, HardwareSerial serial){
  int respBaud = 0;
  int tmp1 = (7 << 5) | id;
  int tmp2 = 0x08;
  int tmp3 = baudrate;
  int tmp4 = tmp3;
  int checksum = (tmp1 ^ tmp2 ^ tmp3 ^ tmp4) & 0x7f; 
  serial.write(0xff); // Header
  serial.write(tmp1); // Data1: Mode:7,ID:31
  serial.write(tmp2); // Data2: 0x08
  serial.write(tmp3); // Data3: 0(921600bps), 1(460800bps), 3(230400bps), 7(115200bps), 15(57600bps), 23(38400bps), 95(9600bps), 191(4800bps)
  serial.write(tmp4); // Data4: =data3
  serial.write(checksum); //Checsum: (Data1 X OR Data2 OR Data3 X OR Data4) AND 0x7F 
  // first byte: Load
  if (serial.available() > 0) {
    // read the incoming byte:
    int ini = Serial.read();
  }
  // second byte: position
  if (serial.available() > 0) {
    // read the incoming byte:
    respBaud = Serial.read();
  }
  
  return respBaud;
}

int WCKLib::pdGainSet(int id, int pGain, int dGain, HardwareSerial serial){
  int d = 0;
  int tmp1 = (7 << 5) | id;
  int tmp2 = 0x09;
  int tmp3 = pGain;
  int tmp4 = dGain;
  int checksum = (tmp1 ^ tmp2 ^ tmp3 ^ tmp4) & 0x7f; 
  serial.write(0xff); // Header
  serial.write(tmp1); // Data1: Mode:7,ID:31
  serial.write(tmp2); // Data2: 0x09
  serial.write(tmp3); // Data3: pGain(1-254)
  serial.write(tmp4); // Data4: dGain(0-254)
  serial.write(checksum); //Checsum: (Data1 X OR Data2 OR Data3 X OR Data4) AND 0x7F 
  // first byte: Load
  if (serial.available() > 0) {
    // read the incoming byte:
    int p = Serial.read();
  }
  // second byte: position
  if (serial.available() > 0) {
    // read the incoming byte:
    d = Serial.read();
  }  
  return d;
}

int WCKLib::pdGainRead(int id, HardwareSerial serial){
  int d = 0;
  int tmp1 = (7 << 5) | id;
  int tmp2 = 0x0A;
  int tmp3 = 0x00;
  int tmp4 = tmp3;
  int checksum = (tmp1 ^ tmp2 ^ tmp3 ^ tmp4) & 0x7f; 
  serial.write(0xff); // Header
  serial.write(tmp1); // Data1: Mode:7,ID:31
  serial.write(tmp2); // Data2: 0x0A
  serial.write(tmp3); // Data3: arbitrary value
  serial.write(tmp4); // Data4: =Data3
  serial.write(checksum); //Checsum: (Data1 X OR Data2 OR Data3 X OR Data4) AND 0x7F 
  // first byte: Load
  if (serial.available() > 0) {
    // read the incoming byte:
    int p = Serial.read();
  }
  // second byte: position
  if (serial.available() > 0) {
    // read the incoming byte:
    d = Serial.read();
  }
  
  return d;
}

int WCKLib::iGainSet(int id, int iGain, HardwareSerial serial){
  int i = 0;
  int tmp1 = (7 << 5) | id;
  int tmp2 = 0x15;
  int tmp3 = iGain;
  int tmp4 = tmp3;
  int checksum = (tmp1 ^ tmp2 ^ tmp3 ^ tmp4) & 0x7f; 
  serial.write(0xff); // Header
  serial.write(tmp1); // Data1: Mode:7,ID:31
  serial.write(tmp2); // Data2: 0x15
  serial.write(tmp3); // Data3: iGain(0-10)
  serial.write(tmp4); // Data4: Data3
  serial.write(checksum); //Checsum: (Data1 X OR Data2 OR Data3 X OR Data4) AND 0x7F 
  // first byte: Load
  if (serial.available() > 0) {
    // read the incoming byte:
    int p = Serial.read();
  }
  // second byte: position
  if (serial.available() > 0) {
    // read the incoming byte:
    i = Serial.read();
  }  
  return i;
}

int WCKLib::iGainReadI(int id, HardwareSerial serial){
  int i = 0;
  int tmp1 = (7 << 5) | id;
  int tmp2 = 0x16;
  int tmp3 = 0x00;
  int tmp4 = tmp3;
  int checksum = (tmp1 ^ tmp2 ^ tmp3 ^ tmp4) & 0x7f; 
  serial.write(0xff); // Header
  serial.write(tmp1); // Data1: Mode:7,ID:31
  serial.write(tmp2); // Data2: 0x16
  serial.write(tmp3); // Data3: arbitrary value
  serial.write(tmp4); // Data4: =Data3
  serial.write(checksum); //Checsum: (Data1 X OR Data2 OR Data3 X OR Data4) AND 0x7F 
  // first byte: Load
  if (serial.available() > 0) {
    // read the incoming byte:
    int p = Serial.read();
  }
  // second byte: position
  if (serial.available() > 0) {
    // read the incoming byte:
    i = Serial.read();
  }
  
  return i;
}

int WCKLib::runtimePdGainSet(int id, int pGain, int dGain, HardwareSerial serial){
  int d = 0;
  int tmp1 = (7 << 5) | id;
  int tmp2 = 0x0B;
  int tmp3 = pGain;
  int tmp4 = dGain;
  int checksum = (tmp1 ^ tmp2 ^ tmp3 ^ tmp4) & 0x7f; 
  serial.write(0xff); // Header
  serial.write(tmp1); // Data1: Mode:7,ID:31
  serial.write(tmp2); // Data2: 0x0B
  serial.write(tmp3); // Data3: pGain(1-254)
  serial.write(tmp4); // Data4: dGain(0-254)
  serial.write(checksum); //Checsum: (Data1 X OR Data2 OR Data3 X OR Data4) AND 0x7F 
  // first byte: Load
  if (serial.available() > 0) {
    // read the incoming byte:
    int p = Serial.read();
  }
  // second byte: position
  if (serial.available() > 0) {
    // read the incoming byte:
    d = Serial.read();
  }  
  return d;
}

int WCKLib::runtimeIGainSet(int id, int iGain, HardwareSerial serial){
  int i = 0;
  int tmp1 = (7 << 5) | id;
  int tmp2 = 0x18;
  int tmp3 = iGain;
  int tmp4 = tmp3;
  int checksum = (tmp1 ^ tmp2 ^ tmp3 ^ tmp4) & 0x7f; 
  serial.write(0xff); // Header
  serial.write(tmp1); // Data1: Mode:7,ID:31
  serial.write(tmp2); // Data2: 0x18
  serial.write(tmp3); // Data3: iGain(0-10)
  serial.write(tmp4); // Data4: Data3
  serial.write(checksum); //Checsum: (Data1 X OR Data2 OR Data3 X OR Data4) AND 0x7F 
  // first byte: Load
  if (serial.available() > 0) {
    // read the incoming byte:
    int p = Serial.read();
  }
  // second byte: position
  if (serial.available() > 0) {
    // read the incoming byte:
    i = Serial.read();
  }  
  return i;
}

