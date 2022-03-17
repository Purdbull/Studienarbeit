#include "Arduino.h"
#include "sPosition.h"

sPosition::sPosition(){
  
}

void sPosition::handle(){
  
}

int sPosition::handle(byte espMsg){
  return ERROR_STATE;
}


int sPosition::handleWithoutParam(){
  //TODO: send its current position
  //if interrupted return error
  //else
  return WAIT_STATE;
}
