#ifndef SENSOR
#define SENSOR

#include "Setup.h"
typedef int Color;

enum Colors{UNDEFINED = -1, YELLOW, WHITE, BLACK, BLUE, RED,GREEN, CLEAR };

class Sensor{ 
public: 
  Color mean[3], sd[3];
  int sensorOutput;

//  int getColor(int number){
//    int frequency;
//    switch(number){
//      case 1:
//        frequency = pulseIn(LEFTSENSEIN,LOW);
//        break;
//      case 2:
//        frequency = pulseIn(LSENSEIN,LOW);
//        break;
//      case 3:
//        frequency = pulseIn(RSENSEIN,LOW);
//        break;
//      case 4:
//        frequency = pulseIn(RIGHTSENSEIN,LOW);
//        break;
//     if(frequency >= mean[YELLOW]-sd[YELLOW] && frequency <= mean[YELLOW]+sd[YELLOW]){
//       Serial.print('Y');
//       return YELLOW;  
//     }else if (frequency >= mean[WHITE]-sd[WHITE] && frequency <= mean[WHITE]+sd[WHITE]){
//      Serial.print('W');
//      return WHITE; 
//     }else if (frequency >= mean[BLACK]-sd[BLACK] && frequency <= mean[BLACK]+sd[BLACK]){
//      Serial.print('B');
//      return BLACK;
//     }
//      Serial.print("No");
//      return UNDEFINED;
//     }
//  };      

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
      Serial.print('Y');
      return YELLOW;  
   }else if (frequency >= mean[WHITE]-sd[WHITE] && frequency <= mean[WHITE]+sd[WHITE]){
      Serial.print('W');
      return WHITE; 
     }else if (frequency >= mean[BLACK]-sd[BLACK] && frequency <= mean[BLACK]+sd[BLACK]){
        Serial.print('B');
        return BLACK;
      }
   Serial.print("No");
   return UNDEFINED;
 };
  void calibrate(int yellowmean,int whitemean,int blackmean,int yellowsd,int whitesd,int blacksd){
   mean[YELLOW] = yellowmean;
   mean[WHITE] = whitemean;
   mean[BLACK]= blackmean;
   sd[YELLOW] = yellowsd;
   sd[WHITE]= whitesd;
   sd[BLACK]= blacksd;  
 };
 
};


#endif


