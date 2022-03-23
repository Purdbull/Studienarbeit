#include "Arduino.h"
#include "State.h"

State::State(){
  //Serial.print("hellothere");
}

State::~State(){
  //Serial.print("hellothere");
}

int State::handle(byte arduinoMsg){
    return ERROR_STATE;
}

int State::handleWithoutParam(){
    return ERROR_STATE;
}

void State::handle(){
  
}
