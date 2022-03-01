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
    return ERROR_STATE;
}

int StartState::handle(byte arduinoMsg){
    return ERROR_STATE;
}

int StartState::handle(){
  Serial.println(this->driveToPosition);
}
