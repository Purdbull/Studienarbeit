#include "Arduino.h"
#include "HighTrainStepper.h"

#ifndef Drivehandler_h
#define Drivehandler_h

class Drivehandler{
  public:
    Drivehandler(int, int, Stepper*);
    ~Drivehandler();

    void drive();

  private:
    Stepper* stepper;
  
    int sectionSpeeds[8] = {20,30,30,40,80,100,90,20};
    int driveSpeeds[8] = {0,0,0,0,0,0,0,0};

    int from;
    int to;
    int driveArrayMaxIndex;
    bool isDrivingForward;

    void setDriveSpeeds();

    
};

#endif
