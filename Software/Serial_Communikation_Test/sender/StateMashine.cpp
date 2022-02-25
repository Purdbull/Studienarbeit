#include "Arduino.h"
#include "StateMashine.h"

StateMashine::StateMashine(){
  currentState = IdleState();
  }

void StateMashine::handle(String serverMsg){
  currentState:handle(serverMsg);
}

void StateMashine::handle(byte arduinoMsg){
  currentState:handle(arduinoMsg);
}
