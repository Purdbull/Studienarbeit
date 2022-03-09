#include "Arduino.h"
#include "IdleState.h"
#include "Decoder.h"

#define IDLE_STATE        0
#define START_STATE       1
#define POSITION_STATE    2
#define END_STATE         3
#define ERROR_STATE       4

#define HEADER_BATTERY    0
#define HEADER_ORDER      1
#define HEADER_POSITION   2
#define HEADER_ACC        3
#define HEADER_ASK        4
#define HEADER_ERROR      5

IdleState::IdleState(){
    this->jarvis = new Decoder();
  }


int IdleState::handle(String serverMsg){
    this->driveToPosition=jarvis->getPosition(serverMsg); 
    return START_STATE;
}

int IdleState::handle(byte arduinoMsg){
    if(jarvis->getHeader(arduinoMsg) == HEADER_BATTERY){
      //TODO: schick battery an server
      Serial.println("akku erhalten, jaja");
      Serial.print("akku liegt bei ");
      Serial.println(jarvis->getBody(arduinoMsg));
      return IDLE_STATE;
    } 
    //TODO: errorMessage
    Serial.println("huch, kein akku! komisch...");
    return ERROR_STATE;  //only battery is allowed
}
