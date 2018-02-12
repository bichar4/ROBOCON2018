

#include "Sensor.h"
#include "Bot.h"
#include "Setup.h"
#include "Helper.h"

Bot bot;
Helper h;
int gameMode;
int direction = 0;
int nodeCount = 0;
int delays[4] ={500,30,0,50}; 
float speedFactor[4] = {1,0.5,0.1,0.5};
  
void setup() {
  //parameter is in setup header.
  Initializer::initializePins();
  bot.initializeBotSensor();
  gameMode = EEPROM.read(0);
  Serial.begin(9600);
  h.SensorCalibration();

}

void loop() {
  //Serial.println(gameMode); 
 if(gameMode!='A'){
   bot.changeMode('A');
   bot.buzzer(1,2000);
   //exit(0);
   while(1){
    bot.testSensor();
   }
   float RPM = 25, rightRPM, leftRPM;
   int error = 0;
   int Kp = 8;
   int leftCount = 0;
   int rightCount = 0;
   while(1){
     error = bot.getError();
     Serial.println(error);
     rightRPM = (RPM + Kp * error); leftRPM = (RPM - Kp * error);
     bot.moveForward(leftRPM,rightRPM);
     rightRPM = rightRPM*speedFactor[(nodeCount%4)];
     leftRPM = leftRPM *speedFactor[(nodeCount%4)];
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
      bot.buzzer((nodeCount%4)); 
      delay(2000);  
      bot.moveLeft(55);
     }
     if(rightCount >=2){      
      delay(delays[nodeCount%4]);
      nodeCount++;
      bot.stopMoving();
      bot.buzzer((nodeCount%4));
      delay(2000); 
      bot.moveRight(55);     
   }
  }
 }

  if(gameMode=='A'){                                                                                                                                                                             
    bot.changeMode('B');
    bot.buzzer(5);
    //exit(0);
    while(1){
     bot.moveForward(maxRPM,maxRPM);
     if(bot.detectWay()==UNDEFINED){
       bot.moveBackward(50,50);
       delay(500);
      }
     bot.moveLeft(50);
     delay(1000);
     bot.stopMoving();
     delay(500);
    }
   }
 
  }  

