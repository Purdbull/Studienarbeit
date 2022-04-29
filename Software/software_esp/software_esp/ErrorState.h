#include "Arduino.h"
#include "State.h"
#include <PubSubClient.h>

#ifndef ErrorState_h
#define ErrorState_h

class ErrorState : public State {
  public:
    PubSubClient* clientPtr;
    ErrorState();
    ~ErrorState();
    ErrorState(char*, PubSubClient*); //
    int handle(String);
    int handle(byte);
    void handle();
};

#endif
