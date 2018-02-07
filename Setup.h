#ifndef SETUP
#define SETUP



#define LEFTMOTORP 1
#define LEFTMOTORM 2
#define LEFTMOTORPWM 3
#define RIGHTMOTORP 4
#define RIGHTMOTORM 5
#define RIGHTMOTORPWM 6
#define LSENSEIN 7 
#define RSENSEIN 8
#define S2 9
#define S3 10
#define MOTORPc 100 //this is nothing :)

class Initializer{
 public:
  static void initializePins(){
    pinMode(LEFTMOTORP,OUTPUT);
    pinMode(LEFTMOTORM,OUTPUT);
    pinMode(LEFTMOTORPWM,OUTPUT);
    pinMode(RIGHTMOTORP,OUTPUT);
    pinMode(RIGHTMOTORM,OUTPUT);
    pinMode(RIGHTMOTORPWM,OUTPUT);
    pinMode(S2,OUTPUT);
    pinMode(S3,OUTPUT);
    pinMode(LSENSEIN,INPUT);
    pinMode(RSENSEIN,INPUT);
     //for activating blue filter for the initial position 
    digitalWrite(S2,LOW);
    digitalWrite(S3,HIGH);
    
  };
};

 
#endif


