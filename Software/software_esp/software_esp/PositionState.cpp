#include "Arduino.h"
#include "PositionState.h"
#include "Decoder.h"
#include "State.h"
#include "PubSubClient.h"
#include <EEPROM.h>

PositionState::PositionState(byte pos, PubSubClient* ptr) {
  this->jarvis = new Decoder();
  this->driveToPosition = pos;
  this->clientPtr = ptr;
}

PositionState::~PositionState() {
  delete (this->jarvis);
}


int PositionState::handle(String serverMsg) {
  this->errorMsg = "position state handler with string called";
  return ERROR_STATE;
}

int PositionState::handle(byte arduinoMsg) {
  if (jarvis->getHeader(arduinoMsg) == HEADER_POSITION) {
    byte pos = jarvis->getBody(arduinoMsg);
    EEPROM.write(0, pos);
    if (pos >= 0 && pos <= 15) {
      if (EEPROM.read(0) != pos) {
        this->clientPtr->publish("Train/Warning", "position was not in sync");
      }
      String p = String(pos);
      this->clientPtr->publish("Train/Position", p.c_str());
      byte positionMsg = this->driveToPosition;
      positionMsg = positionMsg << 2;
      positionMsg = positionMsg | B01000001;
      //delay(500);
      Serial.write(positionMsg);
      return END_STATE;
    }
    this->errorMsg = "invalid position received";
    return ERROR_STATE;
  }
  this->errorMsg = "position msg with wrong header";
  return ERROR_STATE;
}
