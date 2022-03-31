#include "Arduino.h"

#ifndef Drivehandler_h
#define Drivehandler_h

class Drivehandler{
  public:
    Drivehandler(int, int);
    ~Drivehandler();

    void drive();

  private:
    int sectionSpeeds[8] = {0,30,30,40,80,100,90,0};
    int driveSpeeds[8] = {0,0,0,0,0,0,0,0};

    int from;
    int to;
    int driveArrayMaxIndex;
    bool isDrivingForward;

    void setDriveSpeeds();
};

#endif
