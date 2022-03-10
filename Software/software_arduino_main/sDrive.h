#include "Arduino.h"
#include "State.h"

#ifndef sDrive_h
#define sDrive_h

/* Drive State
 * -----------------------------------------------------------
 * 2 tasks:
 * - drive to ordered position
 * - kill and update drive methos if interrupted
 * -----------------------------------------------------------
 * state change:
 * - sDrive; when interrupted, killed and updated drive-method
 * - sError; when something went wrong while driving
 * - sIdle;  when it drove to ordered position
 */

class sDrive : public State{
  public:
    sDrive();
    void handle();
    int handleWithoutParam();
};

#endif
