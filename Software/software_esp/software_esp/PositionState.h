#include "Arduino.h"
#include "State.h"
#include "Decoder.h"

#ifndef PositionState_h
#define PositionState_h

class PositionState : public State {
    public:
        int driveToPosition; 
        Decoder* jarvis;
        PositionState(int);
        int handle(String);
        int handle(byte);

};

#endif