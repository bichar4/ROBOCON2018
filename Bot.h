#ifndef BOT
#define BOT

#include "Sensor.h"
#include "Setup.h"

typedef int MotorDirection;
const MotorDirection FORWARD = 1, BACKWARD = -1, STOP = 0;
int maxRPM = 200;
int previousError = 0;
class Bot{
  Sensor leftSensor,rightSensor;

  public:
  void initializeBotSensor(){
    //
    leftSensor.attach(LSENSEIN);
    rightSensor.attach(RSENSEIN);
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

    void stopMoving(){
    leftMotor(STOP);
    rightMotor(STOP);
     
  };
   
  void leftMotor(MotorDirection motorDirection){
    switch (motorDirection){
      case FORWARD:
        digitalWrite(LEFTMOTORP,HIGH);
        digitalWrite(LEFTMOTORM,LOW);
      break;
      
      case BACKWARD:
        digitalWrite(LEFTMOTORP,HIGH);
        digitalWrite(LEFTMOTORM,LOW);
      break;
      
      case STOP:
        digitalWrite(LEFTMOTORP,LOW);
        digitalWrite(LEFTMOTORM,LOW);
      break;
      
      default:
      break;
    }
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
  
    if (leftSensor.getColor(leftSensor.sensorOutput,BLUE) == WHITE && rightSensor.getColor(rightSensor.sensorOutput,BLUE)== WHITE){
      error = 0;
      previousError = 0;
      }
    if (leftSensor.getColor(LSENSEIN,BLUE) == WHITE && (rightSensor.getColor(RSENSEIN,BLUE)== YELLOW || rightSensor.getColor(RSENSEIN,BLUE)== BLACK)){ 
      error = 1;
      previousError= 1;
      }
    if ((leftSensor.getColor(LSENSEIN,BLUE) == YELLOW || leftSensor.getColor(LSENSEIN,BLUE) == BLACK) && (rightSensor.getColor(RSENSEIN,BLUE)== YELLOW || rightSensor.getColor(RSENSEIN,BLUE)== BLACK) && previousError==1 ){
      error = 2;
      }
    if ((leftSensor.getColor(RSENSEIN,BLUE)== YELLOW ||leftSensor.getColor(RSENSEIN,BLUE)== BLACK) && rightSensor.getColor(LSENSEIN,BLUE) == WHITE){
      error = -1;
      previousError = -1;
      
      }
    if ((leftSensor.getColor(LSENSEIN,BLUE) == YELLOW || leftSensor.getColor(LSENSEIN,BLUE) == BLACK) && (rightSensor.getColor(RSENSEIN,BLUE)== YELLOW || rightSensor.getColor(RSENSEIN,BLUE)== BLACK) && previousError == -1){
      error = -2;
      }
    return error;
  }

  //test function or get POsition:
//  int getPosition(){
//      int position = 0;
//  
//    if (leftSensor.getColor(leftSensor.sensorOutput,BLUE) == WHITE && rightSensor.getColor(rightSensor.sensorOutput,BLUE)== WHITE){
//      position = 0;
//      previousposition = 0;
//      }
//    if (leftSensor.getColor(LSENSEIN,BLUE) == WHITE && (rightSensor.getColor(RSENSEIN,BLUE)== YELLOW || rightSensor.getColor(RSENSEIN,BLUE)== BLACK)){ 
//      position = 1;
//      previousPosition= 1;
//      }
//    if ((leftSensor.getColor(LSENSEIN,BLUE) == YELLOW || leftSensor.getColor(LSENSEIN,BLUE) == BLACK) && (rightSensor.getColor(RSENSEIN,BLUE)== YELLOW || rightSensor.getColor(RSENSEIN,BLUE)== BLACK) && previousError==1 ){
//      position = 2;
//      }
//    if ((leftSensor.getColor(RSENSEIN,BLUE)== YELLOW ||leftSensor.getColor(RSENSEIN,BLUE)== BLACK) && rightSensor.getColor(LSENSEIN,BLUE) == WHITE){
//      position = -1;
//      previousPosition = -1;
//      
//      }
//    if ((leftSensor.getColor(LSENSEIN,BLUE) == YELLOW || leftSensor.getColor(LSENSEIN,BLUE) == BLACK) && (rightSensor.getColor(RSENSEIN,BLUE)== YELLOW || rightSensor.getColor(RSENSEIN,BLUE)== BLACK) && previousError == -1){
//      position = -2;
//      }
//    return position;
//  }
//  
 };
 
#endif

