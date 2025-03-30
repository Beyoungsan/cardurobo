#include <utility>
#include "Cardu.h"
#include "arduino.h"
#include "Extender.h"
#include "motor.h"
#include <math.h>
#include <Adafruit_VCNL4040.h>
Extender ext1;
HUSKYLENS huskylens;
motor mot3(2,1,0); //top right
motor mot4(4,3,5); //top left
motor mot1(8,7,6); // buttom left
motor mot2(10,9,11); // buttom right

//lcd 20x4
LiquidCrystal_I2C lcd(0x27,20,4);


/*view in the same direction as the pcb */
static int preMillis = 0; 

//speed
int IdealVelocity = 100;
static int speed,speed1, speed2, speed3, speed4, speedL, speedR, speedF, speedB = IdealVelocity; // speeed for motor 1-4, for left, right, front and back

//color sensores

const int BackTcs = 6; // channel on multiplexer
const int RTcs = 1; // channel on multiplexer
const int LTcs = 7; // channel on multiplexer

int Noam  = 0;
int tempProx = 0;
int LcdMillis = 0;
Cardu::Cardu()
{
  
}

void Cardu:: lcd_begin(){
 lcd.init();  
 lcd.backlight();
 lcd.clear();
 lcd.setCursor(0, 2);
 lcd.print(" HL | B L R | VCNL ");
  
 lcd.setCursor(4,3);
 lcd.print("|"); 
  
 lcd.setCursor(12,3);
 lcd.print("|"); 
 lcd.setCursor(0, 0);
 lcd.print("MODE:");
}

void Cardu::begin(){
  Serial.begin(115200);
  Serial.println("started");
  LcdMillis = millis();
  //ext1.begin();
  mot1.begin();
  Noam  = 0;
  lcd_begin();
  }
void Cardu::forward(int speed){
  mot1.clwise(speed);
  mot2.counterclwise(speed);
  mot4.clwise(speed);
  mot3.counterclwise(speed);
  }
void Cardu::backwrard(int speed){
  mot1.counterclwise(speed);
  mot2.clwise(speed);
  mot4.counterclwise(speed);
  mot3.clwise(speed);
  }
void Cardu::stop(){
  mot1.neutral();
  mot2.neutral();
  mot3.neutral();
  mot4.neutral();
  }

void Cardu::turnR(int speed){
  mot1.counterclwise(speed);
  mot2.counterclwise(speed);
  mot3.counterclwise(speed);
  mot4.counterclwise(speed);
  }
void Cardu::turnL(int speed){
  mot1.clwise(speed);
  mot2.clwise(speed);
  mot3.clwise(speed);
  mot4.clwise(speed);
  } 
void Cardu::goLeft(int speed){
  mot1.clwise(speed);
  mot2.clwise(speed);
  mot4.counterclwise(speed);
  mot3.counterclwise(speed);
  }
void Cardu::goRight(int speed){
  mot1.counterclwise(speed);
  mot2.counterclwise(speed);
  mot4.clwise(speed);
  mot3.clwise(speed);
  }
void Cardu::diagFL(int speed){
  mot1.clwise(speed);
  mot3.counterclwise(speed);
  mot2.neutral();
  mot4.neutral();
  }
void Cardu::diagBR(int speed){
  mot3.clwise(speed);
  mot1.counterclwise(speed);
  mot2.neutral();
  mot4.neutral();
  }

void Cardu::Calc_Fsteer(){
  //float ratio[4] = {1,1,1,1};
  float x = check(ball_ID).xCenter;// can be between 0 to 320
  float y = check(ball_ID).yCenter;// can be between 0 to 240
  float Ratdis = ((float)(x - 160))/160; // returns a value between -1 to 1
  /*Ratdis = map(Ratdis*(y),-240,240,-1,1);
  Serial.println(Ratdis);*/
 Ratdis = Ratdis *(y*1.5 / 240);
  /*Serial.print("x:");
  Serial.println(x);
  Serial.print("Ratdis:");
  Serial.println(Ratdis);*/
  IdealVelocity = map(check(ball_ID).yCenter, 0, 240, 125, 50); 
  speedL = IdealVelocity*(1+Ratdis); // determins the ratio between left and right
  if(speedL > 255){speedL = 255;} // speed must be between 0 to 255 (2^8)
  speedR = IdealVelocity*(1-Ratdis);
  if(speedR > 255){speedR = 255;}
  }

void Cardu::Calc_Side_steer(){
  int x = check(ball_ID).xCenter; 
  
  }

  
void Cardu::Move_pid(){
  int speed = map(check(ball_ID).yCenter, 0, 220, 250, 30); 
  speed1 = speed;
  speed2 = speed;
  speed3 = speed;
  speed4 = speed;
  }

void Cardu::followBall(){
  /*if(check(ball_ID).yCenter < 200) { 
    Calc_Fsteer();
    int r = speedR;
    int l = speedL;
  
    mot1.clwise(r);
    mot2.counterclwise(l);
    mot4.clwise(r);
    mot3.counterclwise(l);
  }
  else{
    int x = check(ball_ID).xCenter;
    if(x < 140){
      goLeft(abs(160 - x));
      Serial.println("L ");
    }
    else if(x < 180){
      goRight(abs(160 - x));
      Serial.println("R ");
    }
    else{
   //forward with vcnl pid
    forward(250);
    Serial.println("vcnl");
    }
  }
  */
      int x = check(ball_ID).xCenter;
      Calc_Fsteer();
      int r = speedR;
      int l = speedL;

      mot1.clwise(r);
      mot2.counterclwise(l);
      mot4.clwise(r);
      mot3.counterclwise(l);
      }  
void Cardu::closeToBall(){
  if(check(ball_ID).xCenter < 150){
    turnL(30);
  }
  else if(check(ball_ID).xCenter > 170){
    turnR(30);
  }
  else{
    forward(70);
  }
}


int Cardu::IsOnField(){ // returns 1 if on field, 0 see a line and moves according to the line
  if(checkLine(RTcs) == 1 && checkLine(LTcs) == 1){
    backwrard(100);
    delay(500);
    return 0;
  }
  else if(checkLine(RTcs) == 1){
    goLeft(100);
    delay(500); 
    return 0; 
  }
  else if(checkLine(LTcs) == 1){
    goRight(100);
    Serial.println("going right");
    delay(500);  
    return 0;
  }
  else if(checkLine(BackTcs) == 1){
    forward(100);
    Serial.println("going forward");
    delay(500);  
    return 0;
  }
  else{
    return 1; // good to go
  }
  /*if(checkLine(LTcs) == 1){
    backwrard(150);
    Serial.println("going back");
    delay(500);  
    return 0;
  }
  else if(checkLine(BackTcs) == 1){
    forward(100);
    Serial.println("going forward");
    delay(500);  
    return 0;
  }
  else{
    return 1 ; 
  }
  */
}

void Cardu::spinWithBall(int speed){
  
    mot1.clwise(0);
    mot2.clwise(0);
    mot3.counterclwise(speed);
    mot4.counterclwise(speed);
  }
  
  

int Cardu:: FindGoal(){
  int preMillis = millis();
  if(IsOnField() == 1 && !(check(goal1_ID).command == COMMAND_RETURN_BLOCK)) {
    spinWithBall(60);
    return 0;
  }
  return 1;
  
}
/*void Cardu::kick(){
  forward(250);
  delay(1000);
  Noam = 0;
}
*/
int Cardu::vcnlMoving(){
  int dis = GetProximity();
  if(dis < 11){
    return -1; // doesnt see ball
  }
  if(dis < 1000){
    forward(60);
  }
  else{
    kick();
    loadKick();
    delay(1000);
    holdKick();
    }

  return 1;
}
int Cardu::checkProx(){
  int dis = GetProximity();
  if(dis < 11){
    return 0 ; //doesnt see ball
  }
  if(dis < 1000){
    return 1;
  }
  if(dis >= 1000){
    return 2; 
  }
  else{
    return -1;
  }
}
/*void Cardu::Calc_PIDsteer(int kp, int ki, int kd){
  //float ratio[4] = {1,1,1,1};
  float x = check(ball_ID).xCenter;// can be between 0 to 320
  float y = check(ball_ID).yCenter;// can be between 0 to 240
  float error = (x - 160); // returns a value between -1 to 1
  unsigned long currentTime = micros();
  double elapsedTime = (currentTime - previousTime) / 1000000.0

  if (error * lastError < 0) {  // If error changes sign (direction), reset integral
    integralflag = true;  // Set flag to indicate error has changed direction
    cumError = 0;         // Reset cumulative error when direction changes
    //Serial.println("Error changed direction, resetting integral accumulator.");
  } else {
    integralflag = false;  // Continue accumulating integral error
  }
  if (!integralflag){
    cumError += error * elapsedTime;  // Compute integral (accumulate error over time)
  }
 if (elapsedTime > 0) {  // Compute derivative deltaError/deltaTime, avoid dividing by 0
    double rateError = (error - lastError) / elapsedTime;
  double out = kp * error + ki * cumError + kd * rateError;

    // Update for next iteration
    lastError = error;              // Remember current error
    previousTime = currentTime;     // Remember current time

    // Limit the output for smoother operation
    if (out > 254) { out = 254; }
    if (out < -254) { out = -254; }
    Serial.print("degrees = ");  Serial.println(degrees);
    Serial.print("out value = ");  Serial.println(out);
    return out;  // Return the PID output value
}*/

int Cardu::sideMove(){
  double x = check(ball_ID).xCenter;
  double k = 1.5;
  if(x < 140){
    goLeft(int((160.0 - x)*k));
    return 1;
  }
  else if(x > 180){
    goRight(int((x - 160.0)*k));
    return 2;
  }
  else{
    return 0;
  }
}
void Cardu::GoalKeeper(){
  if(IsOnField() == 1){
    if(check(ball_ID).command == COMMAND_RETURN_BLOCK){
      if(sideMove() == 0 ){
        stop();//go to kick
      }
    }
    stop();
  } 
}

int Cardu:: findBall(int speed, int preMillis)
{
  /*Serial.print("preMillis is:");
  Serial.println(preMillis);
  Serial.print("currMillis is:");
  Serial.println(millis());
  Serial.print("time past is:");
  Serial.println(millis() - preMillis);*/
  if (check(ball_ID).command == COMMAND_RETURN_BLOCK)
   return 1;

  if (millis() - preMillis < 2000)
  {
   if (check(ball_ID).command == COMMAND_RETURN_BLOCK)
    return 1;
   backwrard(speed); 
  }
  else if (millis() - preMillis < 5000)
  {
   if (check(ball_ID).command == COMMAND_RETURN_BLOCK)
    return 1;
   turnR(speed/2); //instead of turn right, it will turn the direction it last saw the ball on husky - updated every timr on stat 1
  }
  else
  stop();
   
  return -1;
}
void Cardu:: lcd_stats(int s, int e, int g, int m){ 
  Serial.print("back - ");
  Serial.println(back);
  Serial.print("left - ");
  Serial.println(left);
  Serial.print("right - ");
  Serial.println(right);
  lcd.setCursor(0, 0);
  lcd.print("MODE:");
  if (m==0) {
   lcd.setCursor(7, 0);
   lcd.print("Search Ball");
  }
  else if (m==1){
   lcd.setCursor(7, 0);
   lcd.print("Follow Ball");
  }
   else{
   lcd.setCursor(7, 0);
   lcd.print("Kick Ball  ");
  }

  lcd.setCursor(0, 2);
  lcd.print(" HL | B L R | VCNL ");
  
  lcd.setCursor(4,3);
  lcd.print("|"); 
  
  lcd.setCursor(12,3);
  lcd.print("|"); 
  if(!back){
    lcd.setCursor(6,3);
    lcd.print("X");
  }
  else{
    lcd.setCursor(6,3);
    lcd.print("V");

  }
  if(!left){
    lcd.setCursor(8,3);
    lcd.print("X");
  }
  else{
    lcd.setCursor(8,3);
    lcd.print("V");
  }
  if(!right){
    lcd.setCursor(10,3);
    lcd.print("X");
  }
  else{
    lcd.setCursor(10,3);
    lcd.print("V");
  }
  lcd.setCursor(1,3);
  lcd.print("V");
  lcd.setCursor(15,3);
  lcd.print("V");
}

void Cardu::lcdPrint(int mode){
  if(millis() - LcdMillis > 400){
    lcd_stats(1,2, 3, mode);
     LcdMillis = millis();

  }

}
