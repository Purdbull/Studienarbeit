#include "Arduino.h"
#include "ErrorState.h"
#include "State.h"

ErrorState::ErrorState(String msg, EspMQTTClient* ptr){
    this->errorMsg = msg;
    this->clientPtr = ptr;
  }


int ErrorState::handle(String serverMsg){
  this->errorMsg = "error handler with param called";
  return ERROR_STATE;
}

int ErrorState::handle(byte arduinoMsg){
  this->errorMsg = "error handler with param called";
  return ERROR_STATE;
}

void ErrorState::handle(){
  this->clientPtr->publish("train/error", this->errorMsg);
}
