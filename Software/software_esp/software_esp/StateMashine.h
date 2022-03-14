#include "Arduino.h"
#include "State.h"
#include "IdleState.h"
#include "EspMQTTClient.h"

#ifndef StateMashine_h
#define StateMashine_h

class StateMashine{
  State *currentState;
  EspMQTTClient* clientPtr;

  public:
    StateMashine(EspMQTTClient*);
    void handle(String);
    void handle(byte);
};

#endif 
