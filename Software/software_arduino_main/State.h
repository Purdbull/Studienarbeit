#include "Arduino.h"

#ifndef State_h
#define State_h

#define IDLE_STATE      0
#define POSITION_STATE  1
#define WAIT_STATE      2
#define DRIVE_STATE     3
#define CHARGE_STATE    4
#define OFF_STATE       5
#define ERROR_STATE     6

#define HEADER_BATTERY    0
#define HEADER_ORDER      1
#define HEADER_POSITION   2
#define HEADER_ACC        3
#define HEADER_ASK        4

class State{
    public:
        virtual State();
        virtual ~State();
        virtual int handle(byte);
        virtual int handleWithoutParam();
        virtual void handle();
        int driveToPosition;
        String errorMsg;
};

#endif
