#include "Arduino.h"
#include "State.h"

#ifndef sCharge_h
#define sCharge_h

/* Charge State
 * -----------------------------------------------------------
 * 2 tasks:
 * - driving back to chargingstation
 * - turning off when arrived
 * -----------------------------------------------------------
 * state change:
 * - sError; if its not able to drive back or not arrived
 * - sOff;   turning it off
 */

class sCharge : public State{
  public:
    sCharge();
    void handle();
    int handle(byte);
    int handleWithoutParam();
};

#endif
