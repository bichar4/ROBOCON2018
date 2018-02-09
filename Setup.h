#ifndef SETUP
#define SETUP


#define LEFTMOTORPWM 2
#define LEFTMOTORP 4
#define LEFTMOTORM 3

#define RIGHTMOTORP 5
#define RIGHTMOTORM 6
#define RIGHTMOTORPWM 7

#define LSENSEIN 9  //these are use for calibration
#define RSENSEIN 8

#define LEFTSENSEIN 14  // theese are left most sensor and right most sensor 
#define RIGHTSENSEIN 15
#define S0 9
#define S1 10
#define S2 11
#define S3 12

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
    //fo setting up the frequency
    digitalWrite(S0,LOW);
    digitalWrite(S1,HIGH);
    
  };
};

 
#endif


