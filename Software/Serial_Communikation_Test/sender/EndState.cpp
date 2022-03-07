#include "Arduino.h"
#include "EndState.h"

#define IDLE_STATE      0
#define START_STATE     1
#define POSITION_STATE  2
#define END_STATE       3
#define ERROR_STATE     4

EndState::EndState(){}


int EndState::handle(String serverMsg){
    return ERROR_STATE;
}

int EndState::handle(byte arduinoMsg){
    if(true){ //acc
      Serial.println("acc");
      return IDLE_STATE;
    }else{  //dec
      return ERROR_STATE;
    }
}
