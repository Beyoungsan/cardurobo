//                                                                                                                                בס"ד
#include "Cardu.h"
#include <string.h>
// ☆.。.:*・°☆.。.:*・°☆.。.:*・°☆.。.:*・°☆ 
// ☆.。.:*・°☆.。.:*・°☆.。.:*・°☆.。.:*・°☆

Cardu card; 

int status = 0;
unsigned long preMillis = 0;
unsigned long LcdMillis = millis();

void setup(){
 //card.STbegin();
 card.GKbegin();
}

void loop(){
 //card.STloop();
 lcd.setCursor(8, 1);
 float x = get_gyro();
 String str = String(x,2);
 lcd.print(str);
 card.GKloop();

}
