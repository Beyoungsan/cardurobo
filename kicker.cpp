#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include "Cardu.h"
#include "Extender.h"

Extender extK;
void kick(){
  extK.MotorWrite(14,120);
  extK.MotorWrite(15,0);
  Serial.println("kicking");
  delay(350);
}
void loadKick(){
  extK.MotorWrite(14,50);
  extK.MotorWrite(15,0);
  delay(200);
  extK.MotorWrite(14,42);
  extK.MotorWrite(15,0);
  Serial.println("loading");
}
void holdKick(){
  extK.MotorWrite(14,0);
  extK.MotorWrite(15,0);
  Serial.println("waiting");
}