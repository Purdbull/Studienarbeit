#include "Arduino.h"
#include "StateMashine.h"

StateMashine::StateMashine(){
  currentState = new IdleState();
  }

void StateMashine::handle(String serverMsg){
  int newState = currentState->handle(serverMsg);
}

void StateMashine::handle(byte arduinoMsg){
  int newState = currentState->handle(arduinoMsg);
}
