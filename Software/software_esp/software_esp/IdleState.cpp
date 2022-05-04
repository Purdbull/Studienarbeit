#include "Arduino.h"
#include "IdleState.h"
#include "Decoder.h"
#include "State.h"
#include "PubSubClient.h"

IdleState::IdleState(PubSubClient* ptr){
    this->jarvis = new Decoder();
    this->clientPtr = ptr;
  }

IdleState::~IdleState(){
  delete (this->jarvis);
}


int IdleState::handle(String serverMsg){
    this->driveToPosition=this->jarvis->getPosition(serverMsg); 
    return START_STATE;
}

int IdleState::handle(byte arduinoMsg){
    if(jarvis->getHeader(arduinoMsg) == HEADER_BATTERY){
      float bat = jarvis->getBody(arduinoMsg)*6.25;
      String buf = String(bat);
      const char* batMsg = buf.c_str();
      this->clientPtr->publish("Train/Battery", batMsg);
      return IDLE_STATE;
    } 
    this->errorMsg = "idle handle with byte called no battery";
    return ERROR_STATE;  //only battery is allowed
}
