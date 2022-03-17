#include "Arduino.h"
#include "sOff.h"

sOff::sOff(){
  
}

void sOff::handle(){
  
}

int sOff::handle(byte espMsg){
  return ERROR_STATE;
}

int sOff::handleWithoutParam(){
  //turn off
  return ERROR_STATE;
}
