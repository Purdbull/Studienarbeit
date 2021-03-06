#include "Arduino.h"
#include "StartState.h"
#include "State.h";

StartState::StartState(){
  }


int StartState::handle(String serverMsg){
    this->errorMsg = "startstate called with string";
    return ERROR_STATE;
}

int StartState::handle(byte arduinoMsg){
    this->errorMsg = "startstate called with byte";
    return ERROR_STATE;
}

int StartState::handleWithoutParam(){
  Serial.write(B01000000);
  return POSITION_STATE;
}
