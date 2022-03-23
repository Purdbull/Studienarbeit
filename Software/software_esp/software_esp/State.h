#include "Arduino.h"

#ifndef State_h
#define State_h

#define IDLE_STATE        0
#define START_STATE       1
#define POSITION_STATE    2
#define END_STATE         3
#define ERROR_STATE       4

#define HEADER_BATTERY    0
#define HEADER_ORDER      1
#define HEADER_POSITION   2
#define HEADER_ACC        3
#define HEADER_ASK        4

class State{
    public:
        State();
        virtual ~State();
        virtual int handle(byte);
        virtual int handle(String);
        virtual int handleWithoutParam();
        virtual void handle();
        int driveToPosition;
        String errorMsg;
};

#endif
