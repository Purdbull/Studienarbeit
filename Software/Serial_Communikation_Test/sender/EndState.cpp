#include "Arduino.h"
#include "EndState.h"

#define IDLE_STATE      0
#define START_STATE     1
#define POSITION_STATE  2
#define END_STATE       3
#define ERROR_STATE     4

EndState::EndState(){}


int EndState::handle(String serverMsg){
    return 3;
}

int EndState::handle(byte arduinoMsg){
    return 3;
}
