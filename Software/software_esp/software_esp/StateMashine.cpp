#include "Arduino.h"
#include "StateMashine.h"
#include "StartState.h"
#include "PositionState.h"
#include "ErrorState.h"
#include "EndState.h"
#include "State.h";

StateMashine::StateMashine(EspMQTTClient* MQTTptr) {
  this->currentState = new IdleState();
  this->clientPtr = MQTTptr;
}

void StateMashine::handle(String serverMsg) {
  switch (currentState->handle(serverMsg)) {
    case IDLE_STATE: {
        String msg = currentState->errorMsg;
        delete(currentState);
        currentState = new ErrorState(msg, this->clientPtr);
        currentState->handle();
        delete(currentState);
        currentState = new IdleState();
      }
      break;

  case START_STATE: {
        int pos = currentState->driveToPosition;
        delete(currentState);
        currentState = new StartState(pos);
        int newState = currentState->handleWithoutParam();
        delete(currentState);
        if (newState == POSITION_STATE) {
          currentState = new PositionState(pos);
        } else {
          String msg = currentState->errorMsg;
          delete(currentState);
          currentState = new ErrorState(msg, this->clientPtr);
          currentState->handle();
          delete(currentState);
          currentState = new IdleState();
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
        String msg = currentState->errorMsg;
        delete(currentState);
        currentState = new ErrorState(msg, this->clientPtr);
        currentState->handle();
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
        String msg = currentState->errorMsg;
        delete(currentState);
        currentState = new ErrorState(msg, this->clientPtr);
        currentState->handle();
        delete(currentState);
        currentState = new IdleState();
      }

      break;
  }
}
