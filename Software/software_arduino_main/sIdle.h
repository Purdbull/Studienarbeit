#include "Arduino.h"
#include "State.h"
#include "BatteryMaster.h"
#include "Decoder.h"

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
        Decoder* jarvis;
        BatteryMaster* batteryMeasure;
        
        sIdle();
        
        void sendBattery(float, float);
        void handle();
        
        int handle(byte);
        int handleWithoutParam();
};

#endif
