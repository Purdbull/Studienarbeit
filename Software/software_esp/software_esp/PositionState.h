#include "Arduino.h"
#include "State.h"
#include "Decoder.h"
#include "PubSubClient.h"

#ifndef PositionState_h
#define PositionState_h

class PositionState : public State {
    public:
    
        PositionState(byte, PubSubClient*);
        ~PositionState();
        PubSubClient* clientPtr;
        Decoder* jarvis;
        int handle(String);
        int handle(byte);

};

#endif
