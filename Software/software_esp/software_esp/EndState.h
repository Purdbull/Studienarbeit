#include "Arduino.h"
#include "State.h"
#include "Decoder.h"

#ifndef EndState_h
#define EndState_h

class EndState : public State {
    public:
        EndState();
        ~EndState();
        Decoder* jarvis;
        int handle(String);
        int handle(byte);

};

#endif
