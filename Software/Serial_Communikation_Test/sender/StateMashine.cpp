#include "Arduino.h"
#include "StateMashine.h"

StateMashine::StateMashine(){
  currentState = State();
  }

void StateMashine::handle(String serverMsg){
  currentState:handle(serverMsg);
  currentState = IdleState();
}

void StateMashine::handle(byte arduinoMsg){
  currentState:handle(arduinoMsg);
}
