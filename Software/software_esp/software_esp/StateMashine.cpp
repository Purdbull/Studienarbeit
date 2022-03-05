#include "Arduino.h"
#include "StateMashine.h"
#include "StartState.h"
#include "PositionState.h"
#include "ErrorState.h"
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



StateMashine::StateMashine() {
  this->currentState = new IdleState();
}

void StateMashine::handle(String serverMsg) {
  switch (currentState->handle(serverMsg)) {
    case IDLE_STATE: {
        delete(currentState);
        currentState = new ErrorState();
      }
      break;

    case START_STATE: {
        int pos = currentState->driveToPosition;
        delete(currentState);
        currentState = new StartState(pos);
        int newState = currentState->handle();
        delete(currentState);
        if (newState == POSITION_STATE) {
          currentState = new PositionState();
        } else {
          currentState = new ErrorState();
        }
      }
      break;

    case POSITION_STATE: {

      }
      break;

    case END_STATE: {

      }
      break;

    case ERROR_STATE: {
        delete(currentState);
        currentState = new ErrorState();
        Serial.println("Error string");
        delete(currentState);
        currentState = new IdleState();
      }

      break;
  }
}

void StateMashine::handle(byte arduinoMsg) {
  switch (currentState->handle(arduinoMsg)) {
    case IDLE_STATE:
      delete(currentState);
      currentState = new IdleState();
      break;

    case START_STATE: {
      }
      break;

    case POSITION_STATE: {

      }
      break;

    case END_STATE: {
        delete(currentState);
        currentState = new EndState();
      }
      break;

    case ERROR_STATE: {
        delete(currentState);
        currentState = new ErrorState();
        Serial.println("Error byte");
        delete(currentState);
        currentState = new IdleState();
      }

      break;
  }
}
