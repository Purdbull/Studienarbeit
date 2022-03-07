#include "Arduino.h"
#include "State.h"
#include "Decoder.h"

#ifndef PositionState_h
#define PositionState_h

class PositionState : public State {
    public:
        Decoder* jarvis;
        PositionState();
        int handle(String);
        int handle(byte);

};

#endif
