
#include "Cardu.h"

Extender ext1;
HUSKYLENS huskylens;
//view in the same direction as the pcb 
motor mot3(2,1,0); //top right
motor mot4(4,3,5); //top left
motor mot1(8,7,6); // buttom left
motor mot2(10,9,11); // buttom right

//lcd 20x4
LiquidCrystal_I2C lcd(0x27,20,4);

//last x val husky saw
int indexBall = 0;
int indexGoal = 0;

//speed
int IdealVelocity = 100;
int speed,speed1, speed2, speed3, speed4, speedL, speedR, speedF, speedB = IdealVelocity; // speeed for motor 1-4, for left, right, front and back

//color sensores
const int BackTcs = 6; // channel on multiplexer
const int RTcs = 1; // channel on multiplexer
const int LTcs = 7; // channel on multiplexer

int L_or_R = 0;// left - 0, R = 1.
Cardu::Cardu()
{
  
}

void Cardu::cardBegin(){
  Serial.begin(115200);
  Serial.println("started");
  LcdMillis = millis();
  mot1.begin();
  lcd_begin();
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

void Cardu::brecks(){
  mot1.Brecks();
  mot2.Brecks();
  mot3.Brecks();
  mot4.Brecks();
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

/*void Cardu::calcSteer()
{
  float x = check(ball_ID).xCenter;// can be between 0 to 320
  float y = check(ball_ID).yCenter;// can be between 0 to 240
  float Ratdis = ((float)(x - 160))/160; // returns a value between -1 to 1
 Ratdis = Ratdis *(y*1.5 / 240);
  /*Serial.print("x:");
  Serial.println(x);
  Serial.print("Ratdis:");
  Serial.println(Ratdis);
  IdealVelocity = map(check(ball_ID).yCenter, 0, 240, 125, 50); 
  speedL = IdealVelocity*(1+Ratdis); // determins the ratio between left and right
  if(speedL > 255){speedL = 255;} // speed must be between 0 to 255 (2^8)
  speedR = IdealVelocity*(1-Ratdis);
  if(speedR > 255){speedR = 255;}
}*/

void Cardu::Calc_Side_steer(int speed, int kp){
  float angle = get_gyro(); 
  float error =  angle * kp;
  if(L_or_R == 0){ // we are going left
    if(error > 0){//make back strong
      
      speedF = speed - error;
      speedB = speed + error;
      if(speedF > 255){speedF = 255;} // speed must be between 0 to 255 (2^8)
      if(speedF < 0){speedF = 0;}
      if(speedB > 255){speedB = 255;} // speed must be between 0 to 255 (2^8)
      if(speedB < 0){speedB = 0;}

    }
    else{// make front strong
      
      speedF = speed - error;
      speedB = speed + error;
      if(speedF > 255){speedF = 255;} // speed must be between 0 to 255 (2^8)
      if(speedF < 0){speedF = 0;}
      if(speedB > 255){speedB = 255;} // speed must be between 0 to 255 (2^8)
      if(speedB < 0){speedB = 0;}
    }
  }
  else{// we are going left
    if(error > 0){// make front strong
      
      speedF = speed + error;
      speedB = speed - error;
      if(speedF > 255){speedF = 255;} // speed must be between 0 to 255 (2^8)
      if(speedF < 0){speedF = 0;}
      if(speedB > 255){speedB = 255;} // speed must be between 0 to 255 (2^8)
      if(speedB < 0){speedB = 0;}
    }
    else{//make back strong
      
      speedF = speed + error;
      speedB = speed - error;
      if(speedF > 255){speedF = 255;} // speed must be between 0 to 255 (2^8)
      if(speedF < 0){speedF = 0;}
      if(speedB > 255){speedB = 255;} // speed must be between 0 to 255 (2^8)
      if(speedB < 0){speedB = 0;}
    }
  }
  Serial.print("front : ");
  Serial.println(speedF);
  Serial.print("back : ");
  Serial.println(speedB);
}


  



void Cardu::followBall(){
  int x = check(ball_ID).xCenter;
  calc_steer();
  int r = speedR;
  int l = speedL;

  mot1.clwise(r);
  mot2.counterclwise(l);
  mot4.clwise(r);
  mot3.counterclwise(l);
  }  

void Cardu::closeToBall(){
  if(check(ball_ID).xCenter < 140){
    turnL(30);
  }
  else if(check(ball_ID).xCenter > 180){
    turnR(30);
  }
  else{
    forward(50);
  }
}


int Cardu::IsOnFieldST(){ // returns 1 if on field, 0 see a line and moves according to the line
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
}
int Cardu::IsOnFieldGK(){ // returns 1 if on field, 0 see a line and moves according to the line
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
  /*else if(checkLine(BackTcs) == 1){
    forward(100);
    Serial.println("going forward");
    delay(150);  
    return 0;
  }*/
  else{
    return 1; // good to go
  }
}

void Cardu::spinWithBall(int speed){
    if(indexGoal > 160)
    {
    mot1.clwise(0);
    mot2.clwise(0);
    mot3.counterclwise(speed);
    mot4.counterclwise(speed);}
    else{
    mot1.clwise(0);
    mot2.clwise(0);
    mot3.clwise(speed);
    mot4.clwise(speed);}
  }
  
  

int Cardu:: FindGoal(){
  int preMillis = millis();
  if(IsOnFieldST() == 1 && !(check(goal1_ID).command == COMMAND_RETURN_BLOCK)) {
    spinWithBall(60);
    return 0;
  }
  return 1;
  
}


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

/*
checking how close are we to the ball with vcnl sensor.
-1 = error (husky problem)
0 = doesn't see ball
1 = see ball far, needs to go forward
2 = close enough tp ball. kick
*/
int Cardu::checkProx(){
  Serial.print("prox is:");
  Serial.println(GetProximity());
  int dis = GetProximity();
  if(dis < 11){
    return 0 ; //doesnt see ball
  }
  if(dis < 400){
    return 1;
  }
  if(dis >= 400){
    return 2; 
  }
  else{
    return -1;
  }
}

int Cardu::sideMove(){
  double x = check(ball_ID).xCenter;
  double k = 0.8;
  if(x < 130){
    L_or_R = 0;
    Calc_Side_steer(int((160.0 - x)*k),1);
    mot1.clwise(speedF);
    mot2.clwise(speedF);
    mot4.counterclwise(speedB);
    mot3.counterclwise(speedB);

    return 1;
  }
  else if(x > 190){
    L_or_R = 1;
    Calc_Side_steer(int((x - 160)*k),1);
    mot1.counterclwise(speedF);
    mot2.counterclwise(speedF);
    mot4.clwise(speedB);
    mot3.clwise(speedB);
    return 2;
  }
  else{
    stop();
    return 0;

  }
}

void Cardu::GoalKeeper(){
  if(IsOnFieldGK() == 1){
    if(check(ball_ID).command == COMMAND_RETURN_BLOCK){
      if(sideMove() == 0 ){
        stop();//go to kick
      }
    }
    stop();
  } 
}

int Cardu:: findBall(int speed)
{
  /*Serial.print("preMillis is:");
  Serial.println(preMillis);
  Serial.print("currMillis is:");
  Serial.println(millis());
  Serial.print("time past is:");
  Serial.println(millis() - preMillis);*/
  Serial.print("index is:");
  Serial.println(indexBall);
  if (check(ball_ID).command == COMMAND_RETURN_BLOCK)
   return 1;

  if (millis() - preMillis < 2000)
  {
   if (check(ball_ID).command == COMMAND_RETURN_BLOCK)
    return 1;
   backwrard(speed); 
  }
  else if (millis() - preMillis < 9000)// turning to the side I last saw the ball
  {
   if (check(ball_ID).command == COMMAND_RETURN_BLOCK)
    return 1;
   if (indexBall > 160) 
   turnR(speed/2); //it will turn the direction it last saw the ball on husky - updated every timr on stat 1
   else
   turnL(speed/2);

  }
  else if (millis() - preMillis < 16000)// turning to the other side 
  {
   if (check(ball_ID).command == COMMAND_RETURN_BLOCK)
    return 1;
   if (indexBall < 160)
   turnR(speed/2); //it will turn the direction it last saw the ball on husky - updated every timr on stat 1
   else
   turnL(speed/2);

  }
  else{
    preMillis = millis();
  }

  return -1;
}

void Cardu:: lcd_stats(){ 
  /*Serial.print("back - ");
  Serial.println(back);
  Serial.print("left - ");
  Serial.println(left);
  Serial.print("right - ");
  Serial.println(right);*/
  lcd.setCursor(0, 0);
  lcd.print("MODE:");
  if (status==0) {
   lcd.setCursor(7, 0);
   lcd.print("Search Ball");
  }
  else if (status==1){
   lcd.setCursor(7, 0);
   lcd.print("Follow Ball");
  }
  else if (status==3)
  {
   lcd.setCursor(7, 0);
   lcd.print("backwards");
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
void Cardu::lcdPrint(){
  if(millis() - LcdMillis > 400){
    lcd_stats();
     LcdMillis = millis();

  }

  }
void Cardu::STbegin()
  {
  cardBegin();
  Wire.begin();
  tcsBegin();
  begin_husky();
  vcnlBegin();
  loadKick();
  delay(1000);
  holdKick();
  }
void Cardu::GKbegin()
  {
  cardBegin();
  Wire.begin();
  tcsBegin();
  begin_husky();
  vcnlBegin();
  begin_gyro1();
  loadKick();
  delay(1000);
  holdKick();
  begin_gyro2();
  }


void Cardu::STloop(){
    Serial.print("stat is : ");
    Serial.println(status);
    lcdPrint();

  if(check(goal1_ID).command == COMMAND_RETURN_BLOCK)
    indexGoal = check(goal1_ID).xCenter;
  if(IsOnFieldST() == 1){
      switch(status){

        case 0 : {
          Serial.print("preMillis is:");
          Serial.println(preMillis);
          Serial.print("currMillis is:");
          Serial.println(millis());
          Serial.print("time past is:");
          Serial.println(millis() - preMillis);

          if (findBall(60) == 1)
          {
            Serial.println("found ball!");
            status = 1;
          } // look for ball
          break;
        }
        case 1 : {
          if(check(ball_ID).command == COMMAND_RETURN_BLOCK)
            indexBall = check(ball_ID).xCenter;

          if(check(ball_ID).yCenter < 200){
            followBall();
            }
          else{
            closeToBall();
            }
          if(checkProx() > 0){
            status = 2;
          }
          else if(!(check(ball_ID).command == COMMAND_RETURN_BLOCK)){
            status = 0;
            preMillis = millis();
            Serial.println("in2");
          }
          
          break;
        }
        case 2 : { 
          if(checkProx() == 0 ){
            status = 0;
            preMillis = millis();
          }
          else if(checkProx() == 1){
            forward(60);// was 45
          }
          else if(checkProx() == 2){
            brecks();
            preMillis = (millis());
            while( (millis() - preMillis < 10000) && (check(goal1_ID).xCenter > 180 || check(goal1_ID).xCenter < 140) && checkProx() != 0){
              spinWithBall(80);
              Serial.println(check(goal1_ID).xCenter);

            }
            if(check(goal1_ID).command == COMMAND_RETURN_BLOCK){
            brecks();
            delay(1000);
            kick();
            loadKick();
            delay(1000);
            holdKick();
            }
            status = 0 ;
            preMillis = millis();
        
          }
          break;
        }
      }
    }
  } 
void Cardu::GKloop(){
  lcdPrint();
  Serial.print("stat is - ");
  Serial.println(status);
  if(IsOnFieldGK() == 1){
      switch(status){

        case 0 : {
          Serial.print("preMillis is:");
          Serial.println(preMillis);
          Serial.print("currMillis is:");
          Serial.println(millis());
          Serial.print("time past is:");
          Serial.println(millis() - preMillis);
          selfAlign();
          if (check(ball_ID).command == COMMAND_RETURN_BLOCK)
          {
            Serial.println("found ball!");
            status = 1;
          } // look for ball
          break;
        }
        case 1 : {
    

          if(check(ball_ID).yCenter < 200){
            sideMove();
            }
          else{
            closeToBall();
            }
          if(checkProx() > 0){
            status = 2;
          }
          else if(!(check(ball_ID).command == COMMAND_RETURN_BLOCK)){
            status = 3;
            preMillis = millis();
            Serial.println("in2");
          }
          
          break;
        }
        case 2 : { 
          if(checkProx() == 0 ){
            status = 3;
            preMillis = millis();
          }
          else if(checkProx() == 1){
            forward(60);
          }
          else if(checkProx() == 2){
          
            brecks();
            //delay(1000);
            kickG();
            loadKick();
            delay(1000);
            holdKick();
            preMillis = (millis());
           
            /*while(checkLine(6) != 1 && millis() - preMillis < 15000) // instead, move to 3.
            {
              backwrard(60);
            }*/
            
            status = 3;
            preMillis = millis();
            }
          break;
          }
        case 3 : {
          preMillis = millis();
          while((get_gyro() > 8 || get_gyro() < -8)&&!(check(ball_ID).command == COMMAND_RETURN_BLOCK)){
            selfAlign();}
          while(!(check(ball_ID).command == COMMAND_RETURN_BLOCK) &&!(checkLine(6) == 1) && millis() - preMillis < 10000){
            backwrard(75);
          }
          if(check(ball_ID).command == COMMAND_RETURN_BLOCK){
            status = 1;
          }
          else{
            status = 0;
          }
          

          break;
        }

        }
      }}


void Cardu::selfAlign(){
  if(get_gyro() > 8){
    turnR(30);
  }
  else if(get_gyro()< -8){
    turnL(30);
  }
  else{
    stop();
  }
}