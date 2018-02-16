#ifndef BOT
#define BOT

#include "Sensor.h"
#include "Setup.h"
#include <EEPROM.h>

typedef int MotorDirection;
enum Direction{LEFT =1,RIGHT,END,JUNCTION};
enum Ways{WAY =1,NOWAY,LEFTLOCK,RIGHTLOCK};
const MotorDirection FORWARD = 1, BACKWARD = -1, STOP = 0;
int maxRPM = 50;
int recordedError;
int previousError = 0;
int previousPostion =0;
  
class Blower{
  public:
    void startIt(int pinNo){
      digitalWrite(pinNo,HIGH);
    };

    void stopIt(int pinNo){
      digitalWrite(pinNo,LOW);
    };
    

};

class Bot{
    Blower fan,cleaner;
   Sensor leftSensor,rightSensor,leftMostSensor,rightMostSensor;
   int leftPWM,rightPWM;
   public:

     void startFan(){
      fan.startIt(FAN);
     }

     void stopFan(){
      fan.stopIt(FAN);
     }

     void startCleaner(){
      cleaner.startIt(CLEANER);
     }

     void stopCleaner(){
      cleaner.stopIt(CLEANER); 
     }
     
    int detectWay(){
      int rightMostColor = rightMostSensor.getColor(RIGHTSENSEIN,'A' );
      int rightColor = rightSensor.getColor(RSENSEIN,'A');
      int leftMostColor = leftMostSensor.getColor(LEFTSENSEIN,'A');
      int leftColor = leftSensor.getColor(LSENSEIN,'A');
      if(leftMostColor ==YELLOW && leftColor == YELLOW && rightColor ==YELLOW && rightMostColor == YELLOW){       
        return WAY;
      }
      else if(leftMostColor!=YELLOW){
        return LEFTLOCK;
      }
      else if(rightMostColor!=YELLOW){
        return RIGHTLOCK;
      }
      else{
        return NOWAY;
      }
    }

     
    int isDirection(){
      int rightMostColor = rightMostSensor.getColor(RIGHTSENSEIN );
      int rightColor = rightSensor.getColor(RSENSEIN);
      int leftMostColor = leftMostSensor.getColor(LEFTSENSEIN);
      int leftColor = leftSensor.getColor(LSENSEIN);
      
      if(leftMostColor == WHITE && (leftColor == WHITE || leftColor == UNDEFINED) ){
        return LEFT; 
      }
      if(rightMostColor ==WHITE && (rightColor == WHITE || rightColor ==UNDEFINED)){
        return RIGHT;
      }
      if(leftMostColor ==WHITE && leftColor ==WHITE && rightColor ==WHITE && rightMostColor ==WHITE){
        return JUNCTION; 
      }
      if(rightMostColor ==BLACK && rightColor ==BLACK && leftColor == BLACK && leftMostColor == BLACK){
        return END;
      }
      
      return UNDEFINED;
   }
    
    void initializeBotSensor(){ 
      //calibrate(int yellowmean,int whitemean,int blackmean,int yellowsd,int whitesd,int blacksd)  
      //1021.00 1057.00 1223.00 821.00
        Serial.println("NCMA");
      leftMostSensor.calibrate(825,400,1450,200,250,200);
      leftSensor.calibrate(550,310,1045,80,80,200);
      rightSensor.calibrate(660,340,1420,150,120,200);
      rightMostSensor.calibrate(730,400,1420,150,150,200);
      
      
    };

    void stopMoving(){
      leftMotor(STOP);
      rightMotor(STOP);   
  };
  
    void testSensor(int mode = 'B'){
      leftMostSensor.getColor(LEFTSENSEIN,mode);
      Serial.print("===");
      leftSensor.getColor(LSENSEIN,mode );
      Serial.print("===");
      rightSensor.getColor(RSENSEIN,mode);
      Serial.print("===");
      rightMostSensor.getColor(RIGHTSENSEIN,mode);
      Serial.println(" ");
      
    }
    
    void leftMotor(MotorDirection motorDirection){
      switch (motorDirection){
        case FORWARD:
          digitalWrite(LEFTMOTORP,HIGH);
          digitalWrite(LEFTMOTORM,LOW);
          break;   
        case BACKWARD:
          digitalWrite(LEFTMOTORP,LOW);
          digitalWrite(LEFTMOTORM,HIGH);
          break;
        case STOP:
          digitalWrite(LEFTMOTORP,LOW);
          digitalWrite(LEFTMOTORM,LOW);
          break;        
        default:
          break;
      }     
  };

   void rotate180(){
    analogWrite(LEFTMOTORPWM,150);
    analogWrite(RIGHTMOTORPWM,150);
    leftMotor(FORWARD);
    rightMotor(BACKWARD);
    delay(1000);
    stopMoving();
    delay(100);
   }
   void rotateRight(int rightRPM = 50){
       int  rightPWM = (rightRPM*255/maxRPM);
      int leftPWM = (rightRPM*255/maxRPM);
      analogWrite(LEFTMOTORPWM, leftPWM);
      analogWrite(RIGHTMOTORPWM, rightPWM);
       leftMotor(FORWARD);
        rightMotor(BACKWARD);
        delay(1000);
   }
    void rotateLeft(int leftRPM = 50){
       int  rightPWM = (leftRPM*255/maxRPM);
      int leftPWM = (leftRPM*255/maxRPM);
      analogWrite(LEFTMOTORPWM, leftPWM);
      analogWrite(RIGHTMOTORPWM, rightPWM);
       leftMotor(BACKWARD);
        rightMotor(FORWARD);
        delay(1000);
   }
    void moveRight(int rightRPM = 50){
      int  rightPWM = (rightRPM*255/maxRPM);
      int leftPWM = (rightRPM*255/maxRPM);
      analogWrite(LEFTMOTORPWM, leftPWM);
      analogWrite(RIGHTMOTORPWM, rightPWM);
      do{
        leftMotor(FORWARD);
        rightMotor(BACKWARD);
      }while(rightSensor.getColor(RSENSEIN)!=WHITE);
      //delay(1000);
      stopMoving();
      delay(100);
  }

  void moveLeft(int leftRPM = 50){
    int  rightPWM = (leftRPM*255/maxRPM);
    int leftPWM = (leftRPM*255/maxRPM);
    analogWrite(LEFTMOTORPWM, leftPWM);
    analogWrite(RIGHTMOTORPWM, rightPWM);
    do{
      leftMotor(BACKWARD);
      rightMotor(FORWARD);
      delay(100);
    } while( leftSensor.getColor(LSENSEIN)!=WHITE);
    //delay(500);
    stopMoving();
    delay(1000);
    
  }
  
   void moveForward(int leftRPM, int rightRPM){
    int rightPWM, leftPWM;
    if(rightRPM>=50){
      rightRPM = 50;  
    }
    if(leftRPM>=50){
      leftRPM = 50;  
    }

    if(rightRPM<=10){
      rightRPM = 10;  
    }
    if(leftRPM<=10){
      leftRPM = 10;  
    }
    
    
    rightPWM = (rightRPM*255/maxRPM);
    leftPWM = (leftRPM*255/maxRPM);
    
    int leftDirection = FORWARD, rightDirection = FORWARD;

    if(rightPWM < 80) rightDirection = STOP;
    if(leftPWM < 80) leftDirection = STOP;

    
    analogWrite(LEFTMOTORPWM, leftPWM);
    analogWrite(RIGHTMOTORPWM, rightPWM);
    
    leftMotor(leftDirection);
    rightMotor(rightDirection);
  };

   void moveBackward(int leftRPM, int rightRPM){
    int rightPWM, leftPWM;
    rightPWM = (rightRPM*255/maxRPM);
    leftPWM = (leftRPM*255/maxRPM);
    analogWrite(LEFTMOTORPWM, leftPWM);
    analogWrite(RIGHTMOTORPWM, rightPWM);
    leftMotor(BACKWARD);
    rightMotor(BACKWARD);
  };
  
    void rightMotor(MotorDirection motorDirection){
      switch (motorDirection){
        case FORWARD:
          digitalWrite(RIGHTMOTORP,HIGH);
          digitalWrite(RIGHTMOTORM,LOW);
          break;        
        case BACKWARD:
          digitalWrite(RIGHTMOTORP,LOW);
          digitalWrite(RIGHTMOTORM, HIGH);
          break;                                                                      
        case STOP:
          digitalWrite(RIGHTMOTORP,LOW);
          digitalWrite(RIGHTMOTORM,LOW);
          break;        
        default:  
          break;
      }
    };

    void buzzer(int count,int times= 200){
      for(int i=0;i<count;i++){
        digitalWrite(BUZZERPIN,HIGH);
        delay(times);
        digitalWrite(BUZZERPIN,LOW);
        delay(times);
      }
    }

   int getError(){
     int error = 0;
     int  leftColor = (leftSensor.getColor(LSENSEIN));
     int rightColor = (rightSensor.getColor(RSENSEIN));
     if(leftColor == UNDEFINED || rightColor == UNDEFINED) return recordedError;
   // Serial.println(rightColor);
   // Serial.println("===");
     if ( leftColor == WHITE && rightColor== WHITE){
        error = 0;      
        previousError = 0;
        }
     if (leftColor == WHITE && (rightColor == YELLOW || rightColor == BLACK)){ 
        error = 1;
        previousError= 1;
        }
     if ((leftColor == YELLOW || leftColor == BLACK) && (rightColor == YELLOW || rightColor == BLACK) && previousError==1 ){
        error = 2;
        }
     if ((leftColor == YELLOW ||rightColor == BLACK) && rightColor  == WHITE){
        error = -1;
        previousError = -1;        
        }
     if ((leftColor == YELLOW || leftColor == BLACK) && (rightColor == YELLOW || rightColor == BLACK) && previousError == -1){
        error = -2;
        }
         recordedError = error;
     return error;    
    }

    void changeMode(int num){
        EEPROM.write(0,0);
        int addr = 0;
        EEPROM.write(addr,num);       
    };

  //TODO rename getError() code to getPosition() and write codefor getError
  //algorithm:
  //variable: currentPosition,previouPOsition
  //curentPostion = get
  //error= curretnPosition-previousPOSITION
  //previousPosition = currentPosition

    
 };
 
#endif

