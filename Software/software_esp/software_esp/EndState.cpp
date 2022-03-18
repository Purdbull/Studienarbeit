#include "Arduino.h"
#include "EndState.h"
#include "State.h"

EndState::EndState() {
  this->jarvis = new Decoder();
}


int EndState::handle(String serverMsg) {
  this->errorMsg = "Endstate Handler with string called";
  return ERROR_STATE;
}

int EndState::handle(byte arduinoMsg) {
  if (jarvis->getHeader(arduinoMsg) == HEADER_ACC) {
    if (jarvis->getBody(arduinoMsg) == 1) {
      //Serial.println("akzeptiert");
      return IDLE_STATE;
    }
    if (jarvis->getBody(arduinoMsg) == 2) {
      //Serial.println("abgelehnt");
      this->errorMsg = "order declined";
    }
  } else{
    this->errorMsg = "wrong header in endstate";
  }
  return ERROR_STATE;
}
