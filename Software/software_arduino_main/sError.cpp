#include "Arduino.h"
#include "sError.h"

sError::sError(){
  
}

sError::~sError(){
  
}

void sError::handle(){
  //TODO emergency break!
  //if fatal error while true
}

int sError::handle(byte espMsg){
  return ERROR_STATE;
}

int sError::handleWithoutParam(){
  return ERROR_STATE;
}
