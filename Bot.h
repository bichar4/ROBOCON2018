#ifndef BOT
#define BOT

#include "Sensor.h"
#include "Setup.h"

typedef int MotorDirection;
const MotorDirection FORWARD = 1, BACKWARD = -1, STOP = 0;
int maxRPM = 200;
int recordedError;
int previousError = 0;
int previousPostion =0;
class Bot{
  Sensor leftSensor,rightSensor;
 int leftPWM,rightPWM;
  public:
  void initializeBotSensor(){
   leftSensor.calibrate();
   rightSensor.calibrate();
  };

    void stopMoving(){
    leftMotor(STOP);
    rightMotor(STOP);
     
  };

  void testSensor(){

    leftSensor.getColor(LSENSEIN ,BLUE);
    rightSensor.getColor(RSENSEIN,BLUE);

  }
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

