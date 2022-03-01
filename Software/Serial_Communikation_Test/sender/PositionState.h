#include "Arduino.h"
#include "State.h"

#ifndef PositionState_h
#define PositionState_h

class PositionState : public State {
    public:
        PositionState();
        int handle(String);
        int handle(byte);

};

#endif
