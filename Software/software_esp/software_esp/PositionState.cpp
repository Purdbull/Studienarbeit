#include "Arduino.h"
#include "PositionState.h"
#include "Decoder.h"
#include "State.h"
#include <EEPROM.h>

PositionState::PositionState(int pos) {
  this->jarvis = new Decoder();
  this->driveToPosition = pos;
}


int PositionState::handle(String serverMsg) {
  this->errorMsg = "position state handler with string called";
  return ERROR_STATE;
}

int PositionState::handle(byte arduinoMsg) {
  if (jarvis->getHeader(arduinoMsg) == HEADER_POSITION) {
    byte pos = (byte)jarvis->getBody(arduinoMsg);
    if (pos >= 0 && pos <= 15) {
      if (EEPROM.read(42) != pos) {
        EEPROM.write(42, pos);
        this->errorMsg = "position was not in sync";
        return ERROR_STATE;
      }

      byte positionMsg = (byte)this->driveToPoition;
      positionMsg << 2;
      positionMsg = positionMsg | B01000001;
      Serial.write(positionMsg);
      return END_STATE;
    }
    this->errorMsg = "invalid position received";
    return ERROR_STATE;
  }
  this->errorMsg = "position msg with wrong header";
  return ERROR_STATE;
}
