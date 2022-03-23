#include "Arduino.h"
#include "State.h"
#include "Decoder.h"

#ifndef IdleState_h
#define IdleState_h

class IdleState : public State {
    public:    
        IdleState();
        ~IdleState();
        Decoder* jarvis;
        int handle(String);
        int handle(byte);
        

};

#endif
