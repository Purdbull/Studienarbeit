#include "Arduino.h"
#include "IdleState.h"
#include "Decoder.h"
#include "State.h"

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
