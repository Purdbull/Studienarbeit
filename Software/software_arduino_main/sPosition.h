#include "Arduino.h"
#include "State.h"

#ifndef sPosition_h
#define sPosition_h

/* Position State
 * --------------------------------------
 * 1 Task:
 * - send position to esp
 * --------------------------------------
 * state change:
 * - sWait; when position is sendt to esp
 * - sError; when reed interrupted
*/
class sPosition : public State {
  public:
    sPosition();
    int handleWithoutParam();
};

#endif
