/* Get tilt angles on X and Y, and rotation angle on Z
 * Angles are given in degrees
 * 
 * License: MIT
 */
#include "cardu.h"

MPU6050 mpu(Wire);
unsigned long timer = 0;

void begin_gyro1() { //before setup delay
  
  byte stat = mpu.begin();
  Serial.print(F("MPU6050 stat: "));
  Serial.println(stat);
  while(stat!=0){ 
    Serial.println("couldn't find gyro");
  } // stop everything if could not connect to MPU6050
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  //delay(1000);
  }

 void begin_gyro2() { //after setup delay
  // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done with gyro!\n");
}

float get_gyro() {
  mpu.update();
	//Serial.print("\tZ : ");
	//Serial.println(mpu.getAngleZ());
  return mpu.getAngleZ();
  }

