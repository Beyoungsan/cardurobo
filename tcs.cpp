#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include "Cardu.h"
// Create an instance of the sensor
Adafruit_TCS34725 tcs = Adafruit_TCS34725( TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_4X);// used to be : TCS34725_INTEGRATIONTIME_50MS now : TCS34725_INTEGRATIONTIME_2_4MS
int Ideal = 80;
bool Line = false;
bool back = false;//tcs 6
bool right = false;//tcs 1
bool left = false;//tcs 7

// Select I2C BUS
void TCA9548A(uint8_t bus){ 
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  //Serial.print(bus);
}


int checkLine(int channel){
  TCA9548A(channel);
 // Serial.println(channel);
 // Read the color values
 uint16_t clear, red, green, blue;
 tcs.getRawData(&red, &green, &blue, &clear); // takes ~50 mili seconds !  way to much
 // Print the values
 /*Serial.print("Red: "); Serial.print(red);
 Serial.print(" Green: "); Serial.print(green);
 Serial.print(" Blue: "); Serial.print(blue);
 Serial.print(" Clear: "); Serial.println(clear);
 //delay(500); // Delay for half a second*/
 if (clear > Ideal) {
   Line = true;
   return 1; // white
 }
 else{
   Line = false;
   return 0; // green
 }
}// return 1 if white, 0 if green 

void tcsBegin() {
 
  // Start I2C communication with the Multiplexer
  Wire.begin();
  TCA9548A(6);
 // Initialize sensor
  
  if (!tcs.begin()) {
    Serial.println("Could not find a TCS34725 sensor in 6");
    back = false;
  }
 else{
  Serial.println("TCS34725 - 6 Found!");
  back = true;}
 TCA9548A(7);
 // Initialize sensor

  if (!tcs.begin()) {
    Serial.println("Could not find a TCS34725 sensor in 7");
    left = false;
  }
  else{
    Serial.println("TCS34725 - 7 Found!");
    left = true;
}
TCA9548A(1);
 // Initialize sensor
  if (!tcs.begin()) {
    Serial.println("Could not find a TCS34725 sensor in 7");
    right = false;
  }
  else{
    Serial.println("TCS34725 - 7 Found!");
    right = true;
}

}
/*void loop() {          how to read the colors
  // put your main code here, to run repeatedly:
 if (checkLine(6)==1)
 {
   Serial.println("Found Line! in6");


 }
 else
  Serial.println("On Field! in6");
  delay(500);
if (checkLine(7)==1)
 {
   Serial.println("Found Line! in7");


 }
 else
  Serial.println("On Field! in7");
  delay(500);


}*/



