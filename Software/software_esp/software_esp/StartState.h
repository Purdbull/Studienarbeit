#include "Arduino.h"
#include "State.h"

#ifndef StartState_h
#define StartState_h

class StartState : public State {
    public:
        StartState();
        int handle(String);
        int handle(byte);
        int handleWithoutParam();
};

#endif
