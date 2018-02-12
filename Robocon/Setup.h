#ifndef SETUP
#define SETUP

#define ERRORCOUNT 5

#define BUZZERPIN 7
#define LEFTMOTORPWM 13
#define LEFTMOTORP 11
#define LEFTMOTORM 12

#define RIGHTMOTORP 8
#define RIGHTMOTORM 9
#define RIGHTMOTORPWM 10

#define LSENSEIN 4  //these are use for calibration
#define RSENSEIN 3

#define LEFTSENSEIN 5   // theese are left most sensor and right most sensor 
#define RIGHTSENSEIN 2
#define S0 90
#define S1 101
#define S2 23
#define S3 45

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
    pinMode(BUZZERPIN,OUTPUT);
    pinMode(S2,OUTPUT);
    pinMode(S3,OUTPUT);
    pinMode(LSENSEIN,INPUT);
    pinMode(RSENSEIN,INPUT);
     //for activating blue filter for the initial position 
    digitalWrite(S2,LOW);
    digitalWrite(S3,HIGH);
    //fo setting up the frequency
    digitalWrite(S0,LOW);
    digitalWrite(S1,HIGH);
    
  };
};

 
#endif


