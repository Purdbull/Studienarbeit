#include "Arduino.h"
#include "StateMaschine.h"



StateMaschine::StateMaschine() {
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
      //todo: errormsg handleing
      delete(currentState);
      currentState = new sError();
      currentState->handle();
      delete(currentState);
      currentState = new sIdle();
      break;


  }
}

void StateMaschine::StateHandle() {

  
 switch (this->currentState->handleWithoutParam()) {
    case IDLE_STATE:
      delete (this->currentState);
      this->currentState = new sIdle;
      break;

    case POSITION_STATE:
      delete(currentState);
      currentState = new sError();
      break;

    case WAIT_STATE:
      delete(currentState);
      currentState = new sWait();
      break;

    case DRIVE_STATE: {
        int pos = currentState->driveToPosition;
        delete(currentState);
        currentState = new sDrive(pos);
      }
      break;

    case CHARGE_STATE:
      delete(currentState);
      currentState = new sCharge();
      break;

    case OFF_STATE:
      delete(currentState);
      currentState = new sOff();
      break;

    case ERROR_STATE:
      //todo: errormsg handleing
      delete(currentState);
      currentState = new sError();
      currentState->handle();
      delete(currentState);
      currentState = new sIdle();
      break;
  }
}

void StateMaschine::handle() {
  if (Serial.available() > 0) {
    byte msg = Serial.read();
    StateMaschine::clearSerialBuffer();
    StateMaschine::StateHandle(msg);
  }
  else {
    StateMaschine::StateHandle();
  }
}

void StateMaschine::clearSerialBuffer() {
  char c;
  while (Serial.available()>0) {
    c = Serial.read();
  }
}
