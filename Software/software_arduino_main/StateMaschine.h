#include "Arduino.h"
#include "State.h"
#include "Decoder.h"
#include "sIdle.h"
#include "sPosition.h"
#include "sWait.h"
#include "sDrive.h"
#include "sCharge.h"
#include "sOff.h"
#include "sError.h"

#ifndef StateMaschine_h
#define StateMaschine_h

class StateMaschine{
  State *currentState;

  public:
    StateMaschine();
    ~StateMaschine();
    
    void StateHandle(byte);
    void StateHandle();
    void handle();
    
    void clearSerialBuffer();
};

#endif 
