#ifndef BOT
#define BOT

#include "Sensor.h"
#include "Setup.h"

typedef int MotorDirection;
enum Direction{LEFT =1,RIGHT};
const MotorDirection FORWARD = 1, BACKWARD = -1, STOP = 0;
int maxRPM = 100;
int recordedError;
int previousError = 0;
int previousPostion =0;


class Bot{
   Sensor leftSensor,rightSensor,leftMostSensor,rightMostSensor;
   int leftPWM,rightPWM;
  public:
  
   int isDirection(){
    int rightMostColor = rightMostSensor.getColor(RIGHTSENSEIN );
    int rightColor = rightSensor.getColor(RSENSEIN);
    int leftMostColor = leftMostSensor.getColor(LEFTSENSEIN);
    int leftColor = leftSensor.getColor(LSENSEIN);
    if((leftMostColor == WHITE) ){
      return LEFT; 
    }
    if(leftColor ==YELLOW && rightColor ==WHITE){
      return RIGHT;
    }
    return UNDEFINED;
   }
    
    void initializeBotSensor(){
        leftMostSensor.calibrate(576,421,1400,90,58,200);
     leftSensor.calibrate(458,311,1400,75,65,200);
       rightSensor.calibrate(418,303,1400,60,40,200);
   
       rightMostSensor.calibrate(471,288,1300,30,30,200);     
    };

    void stopMoving(){
    leftMotor(STOP);
    rightMotor(STOP);   
  };
  
    void testSensor(){
      leftMostSensor.getColor(LEFTSENSEIN,BLUE);
      Serial.print("===");
      leftSensor.getColor(LSENSEIN ,BLUE);
      Serial.print("===");
      rightSensor.getColor(RSENSEIN,BLUE);
      Serial.print("===");
      rightMostSensor.getColor(RIGHTSENSEIN,BLUE);
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

  void moveRight(int rightRPM = 60){
     int  rightPWM = (rightRPM*255/maxRPM);
      int leftPWM = (rightRPM*255/maxRPM);
     analogWrite(LEFTMOTORPWM, leftPWM);
    analogWrite(RIGHTMOTORPWM, rightPWM);
     leftMotor(FORWARD);
    rightMotor(BACKWARD);
    delay(850);
    stopMoving();
    delay(100);
  }

  void moveLeft(int leftRPM = 60){
     int  rightPWM = (leftRPM*255/maxRPM);
      int leftPWM = (leftRPM*255/maxRPM);
     analogWrite(LEFTMOTORPWM, leftPWM);
    analogWrite(RIGHTMOTORPWM, rightPWM);
    leftMotor(BACKWARD);
    rightMotor(FORWARD);
    delay(850);
    stopMoving();
    delay(100);
    
  }
  
   void moveForward(int leftRPM, int rightRPM){
    int rightPWM, leftPWM;
    rightPWM = (rightRPM*255/maxRPM);
    leftPWM = (leftRPM*255/maxRPM);
    analogWrite(LEFTMOTORPWM, leftPWM);
    analogWrite(RIGHTMOTORPWM, rightPWM);
    leftMotor(FORWARD);
    rightMotor(FORWARD);
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

   int getError(){
     int error = 0;
     int  leftColor = (leftSensor.getColor(LSENSEIN));
     int rightColor = (rightSensor.getColor(RSENSEIN));
    if (leftColor == UNDEFINED || rightColor == UNDEFINED) return recordedError;
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

  //TODO rename getError() code to getPosition() and write codefor getError
  //algorithm:
  //variable: currentPosition,previouPOsition
  //curentPostion = get
  //error= curretnPosition-previousPOSITION
  //previousPosition = currentPosition

    
 };
 
#endif

