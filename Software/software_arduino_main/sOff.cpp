#include "Arduino.h"
#include "sOff.h"

sOff::sOff(){
  
}

sOff::~sOff(){
  
}

void sOff::handle(){
  
}

int sOff::handle(byte espMsg){
  return ERROR_STATE;
}

int sOff::handleWithoutParam(){
  //digitalWrite(OFF_PIN, HIGH);
  return ERROR_STATE;
}
