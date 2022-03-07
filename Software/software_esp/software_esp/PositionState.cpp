#include "Arduino.h"
#include "PositionState.h"
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

PositionState::PositionState() {
  this->jarvis = new Decoder();
}


int PositionState::handle(String serverMsg) {
  return ERROR_STATE;
}

int PositionState::handle(byte arduinoMsg) {
  if (jarvis->getHeader(arduinoMsg) == HEADER_POSITION) {
    Serial.print("Position erhalten!");
    Serial.print("Position = ");
    Serial.println(jarvis->getBody(arduinoMsg));
    //TODO: aktuelle position aktualisieren
    return END_STATE;
  }
  return ERROR_STATE;
}
