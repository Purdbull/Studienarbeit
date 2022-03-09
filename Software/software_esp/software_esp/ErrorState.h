#include "Arduino.h"
#include "State.h"

#ifndef ErrorState_h
#define ErrorState_h

class ErrorState : public State {
  public:
    String errorMsg;
    ErrorState(String);
    int handle(String);
    int handle(byte);
    void handle();

};

#endif
