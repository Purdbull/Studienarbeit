#include "Arduino.h"
#include "State.h"

#ifndef StateMaschine_h
#define StateMaschine_h

class StateMaschine{
  State *currentState;

  public:
    StateMaschine();
    void handle(byte);
};

#endif 
