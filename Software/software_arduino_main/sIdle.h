#include "Arduino.h"
#include "State.h"

#ifndef sIdle
#define sIdle_h

/* Idle State
 * --------------------------------------------------
 * 3 Tasks:
 * - check battery
 * - check position message
 * - change if it needs to drive home for charging
 * --------------------------------------------------
 * state change:
 * - sPosition; when a possition message arrived
 * - sCharge;   when battery is low
 * - sIdle;     when battery checked and sendt to esp
 */

class sIdle : public State {
    public:
        sIdle();
        int handle(byte);
        int handleWithoutParam();

};

#endif
