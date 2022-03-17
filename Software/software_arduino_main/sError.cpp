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
  
}
