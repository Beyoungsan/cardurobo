#ifndef CARDU
#define CARDU
#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <HUSKYLENS.h>
#include <Adafruit_VCNL4040.h>
#include <LiquidCrystal_I2C.h>
#include <MPU6050_light.h>
#include <Adafruit_Sensor.h>
#include <math.h>
#include <utility>
#include "Motor.h"
#include "Extender.h"
#include "arduino.h"


#define ID0 0 //not learned results. Grey result on HUSKYLENS screen
#define ball_ID 1//orange. first learned results. colored result on HUSKYLENS screen
#define goal1_ID 2 //second learned results. colored result on HUSKYLENS screen
#define goal2_ID 3 
#define Rlight 7
#define Llight 6
extern HUSKYLENS huskylens;
extern motor mot3; //top right
extern motor mot4;//top left
extern motor mot1; // buttom left
extern motor mot2; // buttom right

extern int IdealVelocity;
extern int speed,speed1, speed2, speed3, speed4, speedL, speedR, speedF, speedB;

//lcd 20x4
extern LiquidCrystal_I2C lcd;
extern unsigned long LcdMillis;
extern bool back ;
extern bool right;
extern bool left;
extern bool husky;


//husky lense : 
void begin_husky();
void printResult(HUSKYLENSResult result);
HUSKYLENSResult* get_all();
HUSKYLENSResult check(int ID);

//tcs color sensor
void TCA9548A(uint8_t bus); //shouldnt be used
int checkLine(int channel);
void tcsBegin(); // must be called from setup

//vcnl4040 proximity
int GetProximity();
void vcnlBegin();

//kicker
void kick();
void kickG();
void loadKick();
void holdKick();
//bool ResFlag = false;

//gyro
void begin_gyro1();
void begin_gyro2();
float get_gyro();
  
//loop
extern int indexBall;
extern int indexGoal;
extern unsigned long preMillis;
extern int status;


/*
0 - look for ball
1 - see ball in huskey. and follow ball
2 - if I saw ball in vcnl & im in 1-  ball should be yours 
*/

extern int tempProx; 
class Cardu
 {
  public : 
  
  Cardu(); 

  void cardBegin(); // must be called from setup ╚(″⚈ᴗ⚈)╗ 
  void forward(int speed); // going forward ╔»[⎚◞⎚]«╝
  void backwrard(int speed); // going backwards
  void goRight(int speed); // going rightwards
  void goLeft(int speed); // going leftwards ( ͝סּ ͜ʖ͡סּ)
  void turnR(int speed); //turning right
  void turnL(int speed);// turning left
  void stop(); // common you dont need a commet for that 〈⊙▂⊙〉natural
  void brecks(); //brecks
  void diagFL(int speed); // going diagnoly to forwrad left.
  void diagFR(int speed); // going diagnoly to forwrad right.
  void diagBL(int speed); // going diagnoly to backward left.
  void diagBR(int speed); // going diagnoly to backward right.
  void attackball(); // going for a fight(ง'̀-'́)ง /|\༼ ʘ益ʘ ༽/|\ 
  
  void calc_steer()// must be called before using the speed static variables
    {
    float x = check(ball_ID).xCenter;// can be between 0 to 320
    float y = check(ball_ID).yCenter;// can be between 0 to 240
    float Ratdis = ((float)(x - 160))/160; // returns a value between -1 to 1
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
  void Calc_Side_steer(int speed, int kp);
  void followBall();
  int IsOnFieldGK();
  int IsOnFieldST();
  void spinWithBall_clw();
  void spinWithBall_counter();
  void spinWithBall(int speed);
  void servoBegin();
  int vcnlMoving();
  int FindGoal();
  /// new stuff
  int checkProx();
  void Calc_PIDsteer(int kp, int ki, int kd);
  void closeToBall();
  int sideMove();
  void GoalKeeper();
  int findBall(int speed);
  void lcd_begin();
  void lcd_stats();
  void lcdPrint();
  void GKloop();
  void STloop();
  void GKbegin();
  void STbegin();
  void selfAlign();
 };

#endif