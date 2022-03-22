#include "Arduino.h"
#include "IdleState.h"
#include "Decoder.h"
#include "State.h"

IdleState::IdleState(){
    this->jarvis = new Decoder();
  }


int IdleState::handle(String serverMsg){
    this->driveToPosition=this->jarvis->getPosition(serverMsg); 
    return START_STATE;
}

int IdleState::handle(byte arduinoMsg){
    if(jarvis->getHeader(arduinoMsg) == HEADER_BATTERY){
      float bat = jarvis->getBody(arduinoMsg)*6.25;
      //TODO: schick battery an server
      digitalWrite(2, HIGH);
      delay(40);
      digitalWrite(2, LOW);
      return IDLE_STATE;
    } 
    this->errorMsg = "idle handle with byte called no battery";
    return ERROR_STATE;  //only battery is allowed
}
