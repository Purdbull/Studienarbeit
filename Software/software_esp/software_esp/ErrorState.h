#include "Arduino.h"
#include "State.h"

#ifndef ErrorState_h
#define ErrorState_h

class ErrorState : public State {
    public:
        ErrorState();
        int handle(String);
        int handle(byte);

};

#endif
