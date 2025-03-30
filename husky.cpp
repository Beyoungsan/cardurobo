
#include "Cardu.h"

//HUSKYLENS green line >> SDA; blue line >> SCL

void begin_husky()
{
  while (!huskylens.begin(Wire))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
        Serial.println(F("2.Please recheck the connection."));
        lcd.setCursor(1,3);
        lcd.print("X");
        delay(100);
    }
    
    huskylens.writeAlgorithm(ALGORITHM_COLOR_RECOGNITION);
}

void printResult(HUSKYLENSResult result){
    if (result.command == COMMAND_RETURN_BLOCK){//result is a block
        Serial.println(String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
    }
    else if (result.command == COMMAND_RETURN_ARROW){//result is an arrow
        Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);
    }
    else{//result is unknown.
        Serial.println("Object unknown!");
    }
}

HUSKYLENSResult* get_all()
{
  if (huskylens.requestBlocks()) {
   HUSKYLENSResult *results = new HUSKYLENSResult[huskylens.countBlocks()];
   Serial.println(String()+F("found ")+huskylens.countBlocks()+F(" colors"));
      for (int i = 0; i < huskylens.countBlocks(); i++)
      {
        //printResult(huskylens.getBlock(i));
        results[i] = huskylens.getBlock(i);
        //printResult(results[i]);
      }
    return results;
}
}

HUSKYLENSResult check(int ID)
{
  
  if (huskylens.requestBlocks()) {
   HUSKYLENSResult result;
    for (int i = 0; i < huskylens.count(ID); i++)
    {
      HUSKYLENSResult result = huskylens.getBlock(ID, i);
      if (result.command == COMMAND_RETURN_BLOCK)
      {
      //printResult(result);
      return result;
      }
      
    }
  return result;
}
 
}
