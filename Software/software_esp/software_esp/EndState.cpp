#include "Arduino.h"
#include "EndState.h"
#include "State.h"
#include "PubSubClient.h"
#include "EEPROM.h"

EndState::EndState(PubSubClient* ptr) {
  this->jarvis = new Decoder();
  this->clientPtr = ptr;
}

EndState::~EndState(){
  delete (this->jarvis);
}

int EndState::handle(String serverMsg) {
  this->errorMsg = "Endstate Handler with string called";
  return ERROR_STATE;
}

int EndState::handle(byte arduinoMsg) {
  if (jarvis->getHeader(arduinoMsg) == HEADER_ACC) {
    if (jarvis->getBody(arduinoMsg) == 1) {
      this->clientPtr->publish("Train/Info", "Success");
      digitalWrite(2, HIGH);
      delay(1000);
      digitalWrite(2, LOW);
      byte pos = EEPROM.read(0);
      String p = String(pos);
      this->clientPtr->publish("Train/Position", p.c_str());
      return IDLE_STATE;
    }
    if (jarvis->getBody(arduinoMsg) == 2) {
      this->errorMsg = "order declined";
    }
  } else{
    this->errorMsg = "wrong header in endstate";
  }
  return ERROR_STATE;
}
