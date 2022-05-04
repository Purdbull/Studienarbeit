#include "Arduino.h"
#include "ErrorState.h"
#include "State.h"
#include <PubSubClient.h>

ErrorState::ErrorState(char* msg, PubSubClient* ptr){ //, EspMQTTClient* ptr
    this->errorMsg = msg;
    this->clientPtr = ptr;
  }

ErrorState::~ErrorState(){
  //delete (this->clientPtr);
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
  this->clientPtr->publish("Train/Error", this->errorMsg);
}
