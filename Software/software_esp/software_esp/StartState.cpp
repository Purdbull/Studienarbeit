#include "Arduino.h"
#include "StartState.h"
#include "State.h";

StartState::StartState(int pos){
  this->driveToPosition=pos;
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
  //TODO positionsanfrage an arduino schicken
  return POSITION_STATE;
}
