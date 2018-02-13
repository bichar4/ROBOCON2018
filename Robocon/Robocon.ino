

#include "Sensor.h"
#include "Bot.h"
#include "Setup.h"
#include "Helper.h"



Bot bot;
Helper h;
int gameMode;
int direction = 0;
int nodeCount = 1;
int delays[4] ={0,400,700,400}; 
//float speedFactor[4] = {1,0.5,0.1,0.5};
  
void setup() {
  //parameter is in se tup header.
  Initializer::initializePins();
   Serial.begin(9600);
  gameMode = EEPROM.read(0);
  bot.initializeBotSensor();


  while(0){
  h.SensorCalibration();
}

}

void loop() {
  //Serial.println(gameMode); 
 if(gameMode!='A'){
   bot.changeMode('A');
   bot.buzzer(1,1000);
   //exit(0);
   while(1){
    //bot.moveForward(50,50);
    bot.testSensor(gameMode);
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
     direction = bot.isDirection();
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
      if(nodeCount ==1 || nodeCount == 8)continue;       
      delay(delays[nodeCount%4]);
      bot.stopMoving();
      delay(1000);  
      bot.buzzer((nodeCount%4));
      bot.moveLeft();
      leftCount = 0;
     }
     
     if(rightCount >=2){      
      bot.buzzer(1);
      nodeCount++;
      if(nodeCount ==1 || nodeCount == 8)continue;
      delay(delays[nodeCount%4]);
      bot.stopMoving();
      delay(1000);
      bot.buzzer((nodeCount%4)); 
      bot.moveRight();
      rightCount  = 0;     
   }
   if(bot.isDirection() == END){
      bot.stopMoving();
      bot.changeMode('A');
      bot.buzzer(15,80);
      exit(0);
       
   }
  }
 }
  
  if(gameMode=='A'){                                                                                                                                                                             
    bot.changeMode('B');
    bot.buzzer(3);
    //exit(0);
    
    while(1){
          bot.moveForward(35,35);
          if(bot.detectWay()==NOWAY){
            bot.stopMoving();  
            bot.buzzer(10,100);
            bot.moveBackward(30,30);
            delay(1500);
            bot.rotate180();
            bot.stopMoving();
            delay(300);
          }        
          if(bot.detectWay()==LEFTLOCK){
            bot.stopMoving();  
            bot.buzzer(10,100);
            bot.moveBackward(30,30);
            delay(1500);
            bot.rotateRight(40);
            //delay(300);
            bot.stopMoving();
            delay(500);
          }
          if(bot.detectWay()==RIGHTLOCK){
            bot.stopMoving();  
            bot.buzzer(10,100);
            bot.moveBackward(30,30);
            delay(1500);
            bot.rotateLeft(40);
            //delay(300);
             bot.stopMoving();
            delay(500);
          }
        }

    }
   //}
 
  }  

