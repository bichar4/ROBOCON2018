#ifndef SENSOR
#define SENSOR

#include "Setup.h"
typedef int Color;
enum Colors{YELLOW, WHITE, BLACK, BLUE, RED,GREEN, CLEAR};

class Sensor{
 int sensorOutput;
 Color mean[3], sd[3];
  Color color[3]; 
  public: 
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
    Serial.println('YELLOW');
    return YELLOW;  
  }else if (frequency >= mean[WHITE]-sd[WHITE] && frequency <= mean[WHITE]+sd[WHITE])
  {
    Serial.println('WHITE');
    return WHITE; 
  }else if (frequency >= mean[BLACK]-sd[BLACK] && frequency <= mean[BLACK]+sd[BLACK]){
    Serial.println('BLACK');
    return BLACK;
  }
 };

void attach( int pinNo){
  sensorOutput = pinNo;
};
 
 void calibrate(){
  
 mean[YELLOW] = 383;
 mean[WHITE] =190;
 mean[BLACK]=1210;
 sd[YELLOW] = 12;
 sd[WHITE]= 8;
 sd[WHITE]= 81;
   
 };
 
 
};


#endif


