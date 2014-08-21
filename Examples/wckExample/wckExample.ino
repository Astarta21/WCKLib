#include <WCKLib.h>



int myPorts[] = {1,0,0,0};
WCKLib wckLib(myPorts);

int led = 13;

void setup()
{
  pinMode(led, OUTPUT);
}

void loop()
{
  digitalWrite(led, HIGH); // turn the LED on (HIGH is the voltage level)
 // positionMove1(16, 2, 20);
  wckLib.positionMove(17, 2, 20, 0);
  delay(1000); // wait for a second
  
  digitalWrite(led, LOW); // turn the LED off by making the voltage LOW
 // positionMove1(16, 2, 120);
  wckLib.positionMove(17, 2, 120, 0);
  delay(1000); // wait for a second
}
