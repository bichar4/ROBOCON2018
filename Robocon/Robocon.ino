

#include "Sensor.h"
#include "Bot.h"
#include "Setup.h"

Bot bot;
int direction = 0;
int nodeCount = 0;
int delays[4] ={450,200,100,200}; 
float speedFactor[4] = {1,0.8,0.5,1};
void setup() {

//parameter is in setup header.
Initializer::initializePins();
bot.initializeBotSensor();
  Serial.begin(9600);

  delay(2000);
}

void loop() {
 //Serial.println(pulseIn(RIGHTSENSEIN , LOW));
 //bot.testSensor();
 //Serial.println(" ");
   float RPM = 50, rightRPM, leftRPM;
  int error = 0;
  int Kp = 25;
  int leftCount = 0;
  int rightCount = 0;
 
//  int direction;
  while(1){
  //Serial.println(pulseIn(LEFTSENSEIN,LOW));
  // bot.testSensor();
 
     error = bot.getError();
     Serial.println(error);
      rightRPM = (RPM + Kp * error); leftRPM = (RPM - Kp * error);
    bot.moveForward(leftRPM,rightRPM);
    direction = bot.isDirection();
    if(direction >0){
      if(direction ==LEFT)leftCount+=1;
      if(direction ==RIGHT)rightCount+=1;
     }else {
      leftCount = 0;
      rightCount=0;
     }
     if(leftCount>=2){   
      delay(delays[nodeCount%4]);
      nodeCount++;
      bot.stopMoving();
      delay(2000);
      bot.moveLeft();
     }
    // if(rightCount >=2){
     // delay(delays[nodeCount%4]);
      //nodeCount++;
      //bot.stopMoving();
      //delay(2000);
      //bot.moveRight();
      
      
    //}
    
     
 }


}
