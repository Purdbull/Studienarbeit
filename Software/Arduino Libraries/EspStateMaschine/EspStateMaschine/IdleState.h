#include "Arduino.h"
#include "State.h"

#ifndef IdleState_h
#define IdleState_h

class IdleState : public State {
    public:
        IdleState() : State();
        void handle(String serverMsg);
        void handle(byte arduinoMsg);

}

#endif