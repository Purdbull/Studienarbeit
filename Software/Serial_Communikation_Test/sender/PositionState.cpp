#include "Arduino.h"
#include "PositionState.h"

#define IDLE_STATE      0
#define START_STATE     1
#define POSITION_STATE  2
#define END_STATE       3
#define ERROR_STATE     4

PositionState::PositionState(){
  Serial.println("constructor positionstate");
  }


int PositionState::handle(String serverMsg){
    return ERROR_STATE;
}

int PositionState::handle(byte arduinoMsg){
  //TODO: aktuelle position aktualisieren
    return END_STATE; //wenn pos erhalten und an arduino geschickt
    return ERROR_STATE; // sonst
}
