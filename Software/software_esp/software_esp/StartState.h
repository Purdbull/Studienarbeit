#include "Arduino.h"
#include "State.h"

#ifndef StartState_h
#define StartState_h

class StartState : public State {
    public:
        StartState(int);
        int driveToPosition;  //0-15
        int handle(String);
        int handle(byte);
        int handle();

};

#endif
