#include "Arduino.h"
#include "StateMashine.h"
#include "StartState.h"
#include "PositionState.h"
#include "ErrorState.h"
#include "EndState.h"
#include "State.h";

StateMashine::StateMashine(PubSubClient* ptr) {
  this->currentState = new IdleState(clientPtr);
  this->clientPtr = ptr;
}

void StateMashine::handle(String serverMsg) {
  switch (currentState->handle(serverMsg)) {
    case IDLE_STATE: {
        char* msg = currentState->errorMsg;
        delete(currentState);
        currentState = new ErrorState(msg, clientPtr); //, this->clientPtr
        currentState->handle();
        delete(currentState);
        currentState = new IdleState(clientPtr);
      }
      break;

    case START_STATE: {
        byte pos = currentState->driveToPosition;
        delete(currentState);
        currentState = new StartState();
        int newState = currentState->handleWithoutParam();
        delay(500);//wait for arduino to change to position state and stop sending battery
        char c; //clear serial buffer
        while (Serial.available() > 0) {
          c = Serial.read();
        }
        delete(currentState);
        if (newState == POSITION_STATE) {
          currentState = new PositionState(pos, clientPtr);
        } else {
          char* msg = currentState->errorMsg;
          delete(currentState);
          currentState = new ErrorState(msg, clientPtr); //(msg, this->clientPtr)
          currentState->handle();
          delete(currentState);
          currentState = new IdleState(clientPtr);
        }
      }
      break;

    case POSITION_STATE: {
        char* msg = currentState->errorMsg;
        delete(currentState);
        currentState = new ErrorState(msg, clientPtr); //(msg, this->clientPtr)
        currentState->handle();
        delete(currentState);
        currentState = new IdleState(clientPtr);
      }
      break;

    case END_STATE: {
        char* msg = currentState->errorMsg;
        delete(currentState);
        currentState = new ErrorState(msg, clientPtr); //(msg, this->clientPtr)
        currentState->handle();
        delete(currentState);
        currentState = new IdleState(clientPtr);
      }
      break;

    case ERROR_STATE: {
        char* msg = currentState->errorMsg;
        delete(currentState);
        currentState = new ErrorState(msg, clientPtr); //(msg, this->clientPtr)
        currentState->handle();
        delete(currentState);
        currentState = new IdleState(clientPtr);
      }

      break;
  }
}

void StateMashine::handle(byte arduinoMsg) {
  switch (currentState->handle(arduinoMsg)) {
    case IDLE_STATE:
      delete(currentState);
      currentState = new IdleState(clientPtr);
      break;

    case START_STATE: {
      }
      break;

    case POSITION_STATE: {

      }
      break;

    case END_STATE: {
        delete(currentState);
        currentState = new EndState(clientPtr);
      }
      break;

    case ERROR_STATE: {
        char* msg = currentState->errorMsg;
        delete(currentState);
        currentState = new ErrorState(msg, clientPtr); //(msg, this->clientPtr)
        currentState->handle();
        delete(currentState);
        currentState = new IdleState(clientPtr);
      }

      break;
  }
}
