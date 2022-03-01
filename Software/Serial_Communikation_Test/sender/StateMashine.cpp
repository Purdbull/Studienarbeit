#include "Arduino.h"
#include "StateMashine.h"
#include "StartState.h"

#define IDLE_STATE      0
#define START_STATE     1
#define POSITION_STATE  2
#define END_STATE       3
#define ERROR_STATE     4


StateMashine::StateMashine() {
  this->currentState = new IdleState();
}

void StateMashine::handle(String serverMsg) {
  int newState = currentState->handle(serverMsg);
  switch (newState) {
    case IDLE_STATE:
      break;

    case START_STATE: {
        int pos = currentState->driveToPosition;
        delete(currentState);
        currentState = new StartState(pos);
      }
      break;

    case POSITION_STATE: {

      }
      break;
      
    case END_STATE: {

      }
      break;
      
    case ERROR_STATE: {

      }
      
      break;
  }
}

void StateMashine::handle(byte arduinoMsg) {
  
}
