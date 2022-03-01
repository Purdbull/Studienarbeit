#include "Arduino.h"
#include "IdleState.h"

#define IDLE_STATE      0
#define START_STATE     1
#define POSITION_STATE  2
#define END_STATE       3
#define ERROR_STATE     4

IdleState::IdleState(){
  }


int IdleState::handle(String serverMsg){
    this->driveToPosition=2; //this is just for testing. TODO: evaluate message
    return START_STATE;
}

int IdleState::handle(byte arduinoMsg){
    return IDLE_STATE;
}
