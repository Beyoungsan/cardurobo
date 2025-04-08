#include "esp32-hal.h"
#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include "Cardu.h"
#include "Extender.h"
Cardu card1;
Extender extK;
void kick(){
  preMillis = millis();
  while(card1.IsOnFieldST()== 1 && millis() - preMillis < 100 ){
    card1.forward(100);}
  while(card1.IsOnFieldST()== 1 && millis() - preMillis < 500 ){
    extK.MotorWrite(14,120);
    extK.MotorWrite(15,0);
    Serial.println("kicking");
    }
  card1.stop();

}
void kickG(){
  card1.forward(100);
  delay(100);
  card1.stop();
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