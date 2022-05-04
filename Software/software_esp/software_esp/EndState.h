#include "Arduino.h"
#include "State.h"
#include "Decoder.h"
#include "PubSubClient.h"

#ifndef EndState_h
#define EndState_h

class EndState : public State {
    public:
        EndState(PubSubClient*);
        ~EndState();
        Decoder* jarvis;
        int handle(String);
        int handle(byte);
        PubSubClient* clientPtr;

};

#endif
