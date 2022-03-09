#include "Arduino.h"
#include "StartState.h"

#define IDLE_STATE      0
#define START_STATE     1
#define POSITION_STATE  2
#define END_STATE       3
#define ERROR_STATE     4

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
  //TODO pos an server schicken
  return POSITION_STATE;
}
