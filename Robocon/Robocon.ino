

#include "Sensor.h"
#include "Bot.h"
#include "Setup.h"
#include "Helper.h"

Bot bot;
Helper h;
int gameMode;
int direction = 0;
int nodeCount = 0;
int delays[4] ={1500,1000,00,1000}; 
//float speedFactor[4] = {1,0.5,0.1,0.5};
  
void setup() {
  //parameter is in setup header.
  Initializer::initializePins();
  bot.initializeBotSensor();
  gameMode = EEPROM.read(0);
  Serial.begin(9600);
    //h.SensorCalibration();
}

void loop() {
  //Serial.println(gameMode); 
 if(gameMode!='A'){
   bot.changeMode('A');
   bot.buzzer(1,1000);
   //exit(0);
   while(0){
    //bot.moveForward(50,50);
    bot.testSensor();
   }
   float RPM = 50, rightRPM, leftRPM;
   int error = 0;
   int Kp = 30;
   int leftCount = 0;
   int rightCount = 0;
   while(1){
    
    while(0){
      Sensor s1;
      Serial.println(s1.getColor(RSENSEIN));
      error = bot.getError();
      Serial.println(error);    
    }


    error = bot.getError();
    leftRPM = (RPM - Kp * error);
    rightRPM = (RPM + Kp * error);
    
     bot.moveForward(leftRPM,rightRPM);
     direction = 0; //bot.isDirection();
     if(direction >0){
      if(direction ==LEFT)leftCount+=1;
      if(direction ==RIGHT)rightCount+=1;
     }else {
      leftCount = 0;
      rightCount=0;
     }
     
     if(leftCount>=2){  
      bot.buzzer(1);
      nodeCount++;
      delay(delays[nodeCount%4-1]);
      bot.stopMoving();
      delay(1000);  
      bot.buzzer((nodeCount%4));
      bot.moveLeft();
      leftCount = 0;
     }
     
     if(rightCount >=2){      
      bot.buzzer(1);
      nodeCount++;
      delay(delays[nodeCount%4]);
      bot.stopMoving();
      delay(1000);
      bot.buzzer((nodeCount%4)); 
      bot.moveRight();
      rightCount  = 0;     
   }
  }
 }

  if(gameMode=='A'){                                                                                                                                                                             
    bot.changeMode('B');
    bot.buzzer(3);
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

