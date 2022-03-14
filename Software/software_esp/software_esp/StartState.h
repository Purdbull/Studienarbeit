#include "Arduino.h"
#include "State.h"
#include "EspMQTTClient.h";

#ifndef StartState_h
#define StartState_h

class StartState : public State {
    public:
        StartState(int);
        int handle(String);
        int handle(byte);
        int handleWithoutParam();
};

#endif
