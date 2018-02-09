#ifndef SENSOR
#define SENSOR

#include "Setup.h"
typedef int Color;

enum Colors{UNDEFINED = -1, YELLOW, WHITE, BLACK, BLUE, RED,GREEN, CLEAR };

class Sensor{
  
 
public: 
  Color mean[3], sd[3];
  //Color color[3];
int sensorOutput;
  int getColor (int sensor, int colorFilter = BLUE){   
    switch(colorFilter){
      case BLUE:
        digitalWrite(S2,LOW);
        digitalWrite(S3,HIGH);
        break;
      case RED:
        digitalWrite(S2,LOW);
        digitalWrite(S3,LOW);
        break;
      case GREEN:
        digitalWrite(S2,HIGH);
        digitalWrite(S3,HIGH);
        break;
      case CLEAR:
        digitalWrite(S2,HIGH);
        digitalWrite(S3,LOW);
        break;    
 } 
 int frequency = pulseIn(sensor, LOW);
  if(frequency >= mean[YELLOW]-sd[YELLOW] && frequency <= mean[YELLOW]+sd[YELLOW]){
    //Serial.println('Y');
    return YELLOW;  
  }else if (frequency >= mean[WHITE]-sd[WHITE] && frequency <= mean[WHITE]+sd[WHITE])
  {
    //Serial.println('W');
    return WHITE; 
  }else if (frequency >= mean[BLACK]-sd[BLACK] && frequency <= mean[BLACK]+sd[BLACK]){
    //Serial.println('B');
    return BLACK;
  }
  //Serial.println("No");
  return UNDEFINED;
 };

void attach( int pinNo){
  sensorOutput = pinNo;
};
 
  void calibrate(){
  
   mean[YELLOW] = 349;
   mean[WHITE] =161;
   mean[BLACK]=1210;
   sd[YELLOW] = 35;
   sd[WHITE]= 35;
   sd[BLACK]= 81;

   Serial.println("IMC");
   
   
 };
 
 
};


#endif


