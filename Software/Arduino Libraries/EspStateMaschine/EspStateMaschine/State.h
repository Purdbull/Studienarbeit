#include "Arduino.h"

#ifndef State_h
#define State_h

abstract class State{
    public:
        State();
        void handle();
}

#endif
