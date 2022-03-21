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
  switch (currentState->handleWithoutParam()) {
    case IDLE_STATE:
      delete(currentState);
      currentState = new sIdle();
      break;

    case POSITION_STATE:
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
  if (Serial.available()) {
    StateMaschine::StateHandle(Serial.read());
    StateMaschine::clearSerialBuffer();
  }
  else {
    StateMaschine::StateHandle();
  }
   
  //StateMaschine::StateHandle(B01000000);
  //StateMaschine::StateHandle(B01001101);
}

void StateMaschine::clearSerialBuffer() {
  char c;
  while (Serial.available()) {
    c = Serial.read();
  }
}
