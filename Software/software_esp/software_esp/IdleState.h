#include "Arduino.h"
#include "State.h"
#include "Decoder.h"
#include "PubSubClient.h"

#ifndef IdleState_h
#define IdleState_h

class IdleState : public State {
    public:    
        IdleState(PubSubClient*);
        ~IdleState();
        PubSubClient* clientPtr;
        Decoder* jarvis;
        int handle(String);
        int handle(byte);
        

};

#endif
