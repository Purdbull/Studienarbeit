#include "Arduino.h"
#include "PositionState.h"

#define IDLE_STATE      0
#define START_STATE     1
#define POSITION_STATE  2
#define END_STATE       3
#define ERROR_STATE     4

PositionState::PositionState(){}


int PositionState::handle(String serverMsg){
    return 2;
}

int PositionState::handle(byte arduinoMsg){
    return 2;
}
