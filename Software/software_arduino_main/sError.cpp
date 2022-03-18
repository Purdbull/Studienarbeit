#include "Arduino.h"
#include "sError.h"

sError::sError(){
  
}

void sError::handle(){
  
}

int sError::handle(byte espMsg){
  return ERROR_STATE;
}

int sError::handleWithoutParam(){
  //TODO emergency break!
  //if fatal error while true
  //else
  return IDLE_STATE;
}
