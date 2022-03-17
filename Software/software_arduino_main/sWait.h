#include "Arduino.h"
#include "State.h"

#ifndef sWait_h
#define sWait_h

/* Wait State
 * ----------------------------------------------------
 * 2 tasks:
 * - check for drive position orders
 * - evaluate received drive order
 * ----------------------------------------------------
 * change state:
 * - sDrive; when order is right and acc is sendt back
 * - sError; when order is wrong or no oder received
 */

class sWait : public State {
  public:
    sWait();
    void handle();
    int handle(byte);
    int handleWithoutParam();
};

#endif
