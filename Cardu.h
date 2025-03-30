#ifndef CARDU
#define CARDU
#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <HUSKYLENS.h>
#include <Adafruit_VCNL4040.h>
#include <LiquidCrystal_I2C.h>
#include "Motor.h"
#define ID0 0 //not learned results. Grey result on HUSKYLENS screen
#define ball_ID 1//orange. first learned results. colored result on HUSKYLENS screen
#define goal1_ID 2 //second learned results. colored result on HUSKYLENS screen
#define goal2_ID 3 
#define Rlight 7
#define Llight 6
//lcd 20x4
extern LiquidCrystal_I2C lcd;
extern int LcdMillis;

extern HUSKYLENS huskylens;
extern motor mot3; //top right
extern motor mot4;//top left
extern motor mot1; // buttom left
extern motor mot2; // buttom right
//husky lense : 
void begin_husky();
void printResult(HUSKYLENSResult result);
HUSKYLENSResult* get_all();
HUSKYLENSResult check(int ID);

//tcs color sensor
void TCA9548A(uint8_t bus); //shouldnt be used
int checkLine(int channel);
void tcsBegin(); // must be called from setup
extern bool back ;
extern bool right;
extern bool left;
extern bool husky;

//vcnl4040 proximity
int GetProximity();
void vcnlBegin();

//kicker
void kick();
void loadKick();
void holdKick();
//bool ResFlag = false;



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

  void begin(); // must be called from setup ╚(″⚈ᴗ⚈)╗ 
  void forward(int speed); // going forward ╔»[⎚◞⎚]«╝
  void backwrard(int speed); // going backwards
  void goRight(int speed); // going rightwards
  void goLeft(int speed); // going leftwards ( ͝סּ ͜ʖ͡סּ)
  void turnR(int speed); //turning right
  void turnL(int speed);// turning left
  void stop(); // common you dont need a commet for that 〈⊙▂⊙〉
  void diagFL(int speed); // going diagnoly to forwrad left.
  void diagFR(int speed); // going diagnoly to forwrad right.
  void diagBL(int speed); // going diagnoly to backward left.
  void diagBR(int speed); // going diagnoly to backward right.
  void attackball(); // going for a fight(ง'̀-'́)ง /|\༼ ʘ益ʘ ༽/|\ 
  //void Move_to_ball(int speed);
  void Move_pid();
  void Calc_Fsteer();// must be called before using the speed static variables
  void Calc_Side_steer();
  void followBall();
  int IsOnField();
  void spinWithBall_clw();
  void spinWithBall_counter();
  void spinWithBall(int speed);
  void servoBegin();
  int vcnlMoving();
  int FindGoal();
  /// neww stuff
  int checkProx();
  void Calc_PIDsteer(int kp, int ki, int kd);
  void closeToBall();
  int sideMove();
  void GoalKeeper();
  int findBall(int speed, int preMillis);
  void lcd_begin();
  void lcd_stats(int s, int e, int g, int m);
  void lcdPrint(int mode);
 };

#endif