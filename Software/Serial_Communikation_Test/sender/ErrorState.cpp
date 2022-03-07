#include "Arduino.h"
#include "ErrorState.h"

#define IDLE_STATE      0
#define START_STATE     1
#define POSITION_STATE  2
#define END_STATE       3
#define ERROR_STATE     4

ErrorState::ErrorState(){}


int ErrorState::handle(String serverMsg){
    return 4;
}

int ErrorState::handle(byte arduinoMsg){
    return 4;
}
