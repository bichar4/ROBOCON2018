

#include "Sensor.h"
#include "Bot.h"
#include "Setup.h"

Bot bot;
void setup() {

//parameter is in setup header.
Initializer::initializePins();
bot.initializeBotSensor();
  Serial.begin(9600);
}

void loop() {
 //Serial.println(pulseIn(RIGHTSENSEIN , LOW));
 //bot.testSensor();
 //Serial.println(" ");
   float RPM = 50, rightRPM, leftRPM;
  int error = 0;
  int Kp = 20;
  int leftCount = 0;
  int rightCount = 0;
 
//  int direction;
 while(1){
  bot.testSensor();
//     error = bot.getError();
//     Serial.println(error);
//    rightRPM = (RPM + Kp * error); leftRPM = (RPM - Kp * error);
//    bot.moveForward(leftRPM,rightRPM);
//     direction = bot.isDirection();
//     if(direction >0){
//      if(direction ==LEFT)leftCount+=1;
//      if(direction ==RIGHT)rightCount+=1;
//     }else {
//      leftCount = 0;
//      rightCount=0;
//     }
//     if(leftCount>=10){
//      bot.moveLeft(70);
//     }
//     if(rightCount >=10){
//      //bot.moveRight();
//     }

     
     
  }


}
