#include <WCKLib.h>

WCKLib wck;

int led = 13;

void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  Serial3.begin(115200);
}

void loop()
{
  digitalWrite(led, HIGH); // turn the LED on (HIGH is the voltage level)
  wck.positionMove(16, 2, 20, Serial);
  wck.positionMove(17, 2, 20, Serial3);
  delay(1000); // wait for a second
  
  digitalWrite(led, LOW); // turn the LED off by making the voltage LOW
  wck.positionMove(16, 2, 120, Serial);
  wck.positionMove(17, 2, 120, Serial3);
  delay(1000); // wait for a second
}