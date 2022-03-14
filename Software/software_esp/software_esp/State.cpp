#include "Arduino.h"
#include "State.h"

int State::handle(String serverMsg){
    return ERROR_STATE;
}

int State::handle(byte arduinoMsg){
    return ERROR_STATE;
}

int State::handleWithoutParam(){
    return ERROR_STATE;
}

void State::handle(){
  
}
