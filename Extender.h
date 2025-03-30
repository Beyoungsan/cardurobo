#ifndef EXTENDER_H
#define EXTENDER_H

 class Extender {

  public:
   void begin();   //must be called from  void setup() 
   void ServoWrite(int num, int value);
   void MotorWrite(int num, int value);

 };
#endif