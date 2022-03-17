#include "Arduino.h"
#include "StateMaschine.h"



StateMaschine::StateMaschine() {
  Serial.begin(9600);
  currentState = new sIdle();
}

void StateMaschine::StateHandle(byte espMsg) {
  switch (currentState->handle(espMsg)) {
    case IDLE_STATE:
      break;

    case POSITION_STATE:
      delete(currentState);
      currentState = new sPosition();
      break;

    case WAIT_STATE:
      break;

    case DRIVE_STATE:
      break;

    case CHARGE_STATE:
      break;

    case OFF_STATE:
      break;

    case ERROR_STATE:
      break;


  }
}

void StateMaschine::StateHandle() {
  switch (currentState->handleWithoutParam()) {
    case IDLE_STATE:
      break;

    case POSITION_STATE:
      break;

    case WAIT_STATE:
      delete(currentState);
      currentState = new sWait();
      break;

    case DRIVE_STATE:
      break;

    case CHARGE_STATE:
      break;

    case OFF_STATE:
      break;

    case ERROR_STATE:
      break;
  }
}

void StateMaschine::handle() {
  if (Serial.available()) {
    StateMaschine::StateHandle(Serial.read());
    StateMaschine::clearSerialBuffer();
  }
  else {
    StateMaschine::StateHandle();
  }
}

void StateMaschine::clearSerialBuffer() {
  char c;
  while (Serial.available()) {
    c = Serial.read();
  }
}
