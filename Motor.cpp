#include "motor.h"
#include "arduino.h"
#include "Extender.h"
Extender ext;
void motor::begin(){
  ext.begin();
}

void motor::clwise(int speed){
  ext.MotorWrite(in1,0);
  ext.MotorWrite(in2,255);
  ext.MotorWrite(en,speed);

  }
void motor::counterclwise(int speed){
  ext.MotorWrite(in1,255);
  ext.MotorWrite(in2,0);
  ext.MotorWrite(en,speed);
  }

  void motor::neutral(){
    ext.MotorWrite(in1,0);
    ext.MotorWrite(in2,0);
  }
  void motor::Brecks(){
    ext.MotorWrite(in1,255);
    ext.MotorWrite(in2,255);
  }



