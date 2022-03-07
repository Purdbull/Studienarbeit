#include "Arduino.h"
#include "State.h"
#include "IdleState.h"

#ifndef StateMashine_h
#define StateMashine_h

class StateMashine{
  State *currentState;

  public:
    StateMashine();
    void handle(String);
    void handle(byte);
};

#endif
