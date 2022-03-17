#include "Arduino.h"
#include "State.h"

int State::handle(byte arduinoMsg){
    return ERROR_STATE;
}

int State::handleWithoutParam(){
    return ERROR_STATE;
}

void State::handle(){
  
}
