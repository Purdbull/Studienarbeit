#include "Arduino.h"
#include "State.h"
//#include "EspMQTTClient.h"

#ifndef ErrorState_h
#define ErrorState_h

class ErrorState : public State {
  public:
    //EspMQTTClient* clientPtr;
    ErrorState();
    ~ErrorState();
    ErrorState(String); //, EspMQTTClient*
    int handle(String);
    int handle(byte);
    void handle();
};

#endif
