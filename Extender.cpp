#include "Extender.h"
#include <Wire.h>
#include "Adafruit_PWMServoDriver.h"


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

void Extender::begin() {
  // put your setup code here, to run once:
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
}

void Extender::ServoWrite(int num, int value) {
  if(value < SERVOMIN)
  {  // treat values less than 544 as angles in degrees (valid values in microseconds are handled as microseconds)
    if(value < 0) value = 0;
    if(value > 180) value = 180;
    value = map(value, 0, 180, 544,  2400);
  }
  pwm.writeMicroseconds(num, value);
}

void Extender::MotorWrite(int num, int value) {
  value = map(value, 0, 255, 544,  15000);
  pwm.writeMicroseconds(num, value);
  //Serial.print(value);
  //Serial.print(" | ");
}