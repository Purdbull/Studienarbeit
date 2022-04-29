#include "Arduino.h"
#include "State.h"
#include "IdleState.h"
#include <PubSubClient.h>

#ifndef StateMashine_h
#define StateMashine_h

class StateMashine{
  State *currentState;
  PubSubClient* clientPtr;

  public:
    StateMashine(PubSubClient*); //EspMQTTClient*
    void handle(String);
    void handle(byte);
};

#endif 
