#include "Arduino.h"

#ifndef State_h
#define State_h

class State{
    public:
        virtual int handle(byte);
        virtual int handle(String);
        virtual int handle();
        int driveToPosition;
};

#endif
