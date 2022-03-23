#include "Arduino.h"
#include "State.h"

#ifndef sError_h
#define sError_h

/* Error State
 * -----------------------------------------------------------
 * 2 tasks:
 * - validate error
 * - change back or hard fault
 * -----------------------------------------------------------
 * state change:
 * - sIdle; when error is validated
 */

class sError : public State{
  public:
    sError();
    void handle();
    int handle(byte);
    int handleWithoutParam();
};

#endif
