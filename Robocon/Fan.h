#include "Setup.h"

class Fan{
  public:
    void fanStart(){
      digitalWrite(FAN,HIGH);    
    }

    void fanStop(){
      digitalWrite(FAN,LOW);  
    }

    void blowerStart(){
      digitalWrite(BLOWER,HIGH); 
    }
    void blowerStop(){
      digitalWrite(BLOWER,LOW);  
    }
  
}
