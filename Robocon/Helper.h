#ifndef HELPER
#define HELPER
#include "Setup.h"
#define MAXSIZE 300
class Helper{
  public: 
    float data[4][MAXSIZE];
    long int sum[4];
    float mean[4],sd[4];
    int frequency[4];

    void indicate(int n){
      int i=0;
      for(i=0;i<n;i++){
        delay(1000);
        digitalWrite(13,HIGH);
        delay(100);
        digitalWrite(13,LOW);
        delay(100);
      } 
   };

   void SensorCalibration(){
      for(int i=0;i<MAXSIZE;i++){
        frequency[0] = pulseIn(LEFTSENSEIN , LOW);
        frequency[1] = pulseIn(LSENSEIN,LOW);
        frequency[2] = pulseIn(RSENSEIN,LOW);
        frequency[3] = pulseIn(RIGHTSENSEIN,LOW);
   
        for(int j=0;j<4;j++){
          Serial.print(frequency[j]);
          Serial.print("--");
        }
    
        Serial.println(" ");
        for(int m = 0;m<4;m++){
         data[m][i] = frequency[m];
        }

        for(int m = 0;m<4;m++){
          sum[m]+=data[m][i];
        }
    }
    indicate(2);
    for(int m = 0;m<4;m++){
      mean[m] = sum[m]/MAXSIZE;
    }   
    for(int i=0;i<MAXSIZE;i++){
      for(int j=0;j<4;j++){
        sum[j]+=((data[j][i]-mean[j])*(data[j][i]-mean[j]));
      }
    }
    for(int m = 0;m<4;m++){
      sd[m] = sqrt(sum[m]/MAXSIZE);
    }

    for(int m= 0;m<4;m++){
      Serial.print(mean[m]);
      Serial.print(" ");
    }
    Serial.println(" ");
 
    for(int m= 0;m<4;m++){
      Serial.print(sd[m]);
      Serial.print(" ");
    }
    Serial.println(" ");
    Serial.println("========================");
  };

};
#endif
