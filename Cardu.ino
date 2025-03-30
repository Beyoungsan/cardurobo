#include "Cardu.h"//                                                                                                                                בס"ד
#include "motor.h"
#include "Extender.h"

// ☆.。.:*・°☆.。.:*・°☆.。.:*・°☆.。.:*・°☆
// ☆.。.:*・°☆.。.:*・°☆.。.:*・°☆.。.:*・°☆
Cardu card; 
Extender extS;
static int status;
static int preMillis;

void setup() {
  //Serial.begin(115200);
  card.begin();
  Wire.begin();
  tcsBegin();
  begin_husky();
  vcnlBegin();
 
  //extS.begin();
  status = 0;
  preMillis = 0;
  int LcdMillis = millis();

}
// && check(ball_ID).yCenter < 220 
void loop(){
  //Serial.println("GetProximity");
  //delay(9000);}
    //Serial.print("stat is : ");
  //card.forward(200);
  card.lcdPrint(status);


 if(card.IsOnField() == 1){
    switch(status){

      case 0 : {
        Serial.print("preMillis is:");
        Serial.println(preMillis);
        Serial.print("currMillis is:");
        Serial.println(millis());
        Serial.print("time past is:");
        Serial.println(millis() - preMillis);

        if (card.findBall(60, preMillis) == 1)
        {
          Serial.println("found ball!");
          status = 1;
        } // look for ball
        break;
      }
      case 1 : {
        if(check(ball_ID).yCenter < 200){
          card.followBall();}
        else{
          card.closeToBall();
          }
        if(card.checkProx() > 0){
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
        if(card.checkProx() == 0 ){
          status = 0;
          preMillis = millis();
        }
        else if(card.checkProx() == 1){
          card.forward(60);
        }
        else if(card.checkProx() == 2){
          preMillis = (millis());
          while( (millis() - preMillis < 5000) && (check(goal1_ID).xCenter > 180 || check(goal1_ID).xCenter < 140)){
            card.spinWithBall(60);
            Serial.println(check(goal1_ID).xCenter);

          }
          card.stop();
          delay(2000);
          kick();
          status = 0 ;
          preMillis = millis();

         }
         break;
      }
    }
  }
}

 
  


   /* if(card.checkProx() == 0 ){
      card.stop();
    }
    if(card.checkProx() == 1){
      card.forward(60);
    }
    if(card.checkProx() == 2){
      while((check(goal1_ID).xCenter > 180 || check(goal1_ID).xCenter < 140)){
        card.spinWithBall(60);
        Serial.println(check(goal1_ID).xCenter);

      }
      card.stop();
      delay(3000);
    }
  }
    
  if(card.IsOnField()){
    if(check(ball_ID).command == COMMAND_RETURN_BLOCK){
      card.followBall();
    }
    else{
      card.stop();
    }
  }
  }
  /*Serial.println(check(goal1_ID).xCenter);
  while((check(goal1_ID).xCenter > 180 || check(goal1_ID).xCenter < 140)){
    card.spinWithBall(60);
    Serial.println(check(goal1_ID).xCenter);

  }
  card.stop();
  delay(3000);*/
  
  
  
  
  
  
  
  /*if(card.IsOnField()== 1 ){
    if(Noam == 0){
      Serial.println("in stat 0");
      card.backwrard(70);//should be spinning;
      if(check(ball_ID).command == COMMAND_RETURN_BLOCK)
       Noam = 1;
    }
    else if (Noam == 1)
    {
      int k = -1;
      Serial.println("in stat 1");
      //if (card.vcnlMoving() == -1){
        if(check(ball_ID).command == COMMAND_RETURN_BLOCK ){
          if (check(ball_ID).yCenter < 220)
          card.followBall();
          else
          k = card.FindGoal();
          }
        else{
          Noam = 0;}
     // }
      if (k == 1){
        Noam = 2;
      }
    }
    else if (Noam == 2){
      Serial.println("in stat 2");
      if (card.vcnlMoving() == -1)
       Noam = 0;
      //card.vcnlMoving();
    }
    
  }// end loop
  
  /*if (check(ball_ID).command == COMMAND_RETURN_BLOCK){
    Serial.print("see ball");
    if(card.IsOnField()== 1 ){
     card.followBall();
     Serial.print("following");
    }
  }
  else{
    if(card.vcnlMoving() == -1){
      card.stop();
    }
    else{
      card.vcnlMoving();
    }
}

  //card.IsOnField();
  //delay(100);
  //card.kick();
  //card.kick();
  //delay(200);
*/
/*if(card.IsOnField() == 1){
  if(card.vcnlMoving() == -1){
      if(check(ball_ID).command == COMMAND_RETURN_BLOCK)
        card.followBall();
      else{
        card.backwrard(80);
        }
  }

}
*/
//GetProximity();

    /*mot1.counterclwise();
    mot2.counterclwise(100);
    mot3.clwise(100);
    mot4.clwise(100);
    delay(500);*/
/*    mot1.clwise(120);
    mot2.counterclwise(60);
    mot3.clwise(160);
    mot4.counterclwise(134);
    delay(500);
    */
    
