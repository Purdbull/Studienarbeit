#include "Arduino.h"
#include "EndState.h"

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

EndState::EndState() {
  this->jarvis = new Decoder();
}


int EndState::handle(String serverMsg) {
  return ERROR_STATE;
}

int EndState::handle(byte arduinoMsg) {
  if (jarvis->getHeader(arduinoMsg) == HEADER_ACC){
    if (jarvis->getBody(arduinoMsg) == 1) {
      Serial.println("akzeptiert");
      return IDLE_STATE;
      }
    if (jarvis->getBody(arduinoMsg) == 2) {
      Serial.println("abgelehnt");
    }
  }
  return ERROR_STATE; 
}
