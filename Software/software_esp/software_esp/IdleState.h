#include "Arduino.h"
#include "State.h"

#ifndef IdleState_h
#define IdleState_h

class IdleState : public State {
    public:
        IdleState();
        int handle(String);
        int handle(byte);
        

};

#endif
