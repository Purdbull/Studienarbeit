#include "Arduino.h"
#include "State.h"

#ifndef EndState_h
#define EndState_h

class EndState : public State {
    public:
        EndState();
        int handle(String);
        int handle(byte);

};

#endif
