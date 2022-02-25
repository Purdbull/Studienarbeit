#include "Arduino.h"
#include "State.h"

#ifndef IdleState_h
#define IdleState_h

class IdleState : public State {
    public:
        IdleState();
        void handle(String);
        void handle(byte);

};

#endif
