#include "Arduino.h"
#include "State.h"

#ifndef sOff_h
#define sOff_h

/* Off State
 * -----------------------------------------------------------
 * 1 task:
 * - turn off the whole system
 * -----------------------------------------------------------
 * state change:
 * - none
 */

class sOff : public State{
  public:
    sOff();
    ~sOff();
    void handle();
    int handle(byte);
    int handleWithoutParam();
};

#endif
