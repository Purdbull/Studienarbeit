#include "Arduino.h"
#include "State.h"
#include "Decoder.h"

#ifndef IdleState_h
#define IdleState_h

class IdleState : public State {
    public:
        Decoder* jarvis;
        IdleState();
        int handle(String);
        int handle(byte);
        

};

#endif
