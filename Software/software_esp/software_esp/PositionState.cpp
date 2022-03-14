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
    Serial.print("Position erhalten!");
    Serial.print("Position = ");
    byte pos = (byte)jarvis->getBody(arduinoMsg);
    if(EEPROM.read(42) != pos){
      EEPROM.write(42, pos);
      this->errorMsg = "position was not in sync";
      return ERROR_STATE;
    }
    EEPROM.write(42, (byte)jarvis->getBody(arduinoMsg));
    Serial.println(EEPROM.read(42));
    //fahrbefehl schicken TODO
    return END_STATE;
  }
  return ERROR_STATE;
}
