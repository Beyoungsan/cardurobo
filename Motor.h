#ifndef MOTOR_H
#define MOTOR_H
#include "arduino.h"
class motor {

  public:

  motor(int _in1, int _in2, int _en){
    in1 = _in1;
    in2 = _in2;
    en = _en;
    //pinMode(in1,OUTPUT);
    //pinMode(in2,OUTPUT);
    //pinMode(en,OUTPUT);


  }
  void clwise(int speed);
  void counterclwise(int speed);
  void neutral();
  void begin();
  void Brecks();

  private:
  int in1;
  int in2;
  int en; 

};

#endif