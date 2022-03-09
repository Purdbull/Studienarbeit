#include "Arduino.h"
#include "ErrorState.h"

#define IDLE_STATE      0
#define START_STATE     1
#define POSITION_STATE  2
#define END_STATE       3
#define ERROR_STATE     4

ErrorState::ErrorState(String msg){
    this->errorMsg = msg;
  }


int ErrorState::handle(String serverMsg){
  this->errorMsg = "error handler with param called";
    return ERROR_STATE;
}

int ErrorState::handle(byte arduinoMsg){
  this->errorMsg = "error handler with param called";
    return ERROR_STATE;
}

void ErrorState::handle(){
  //errorMsg an server schicken TODO
}
