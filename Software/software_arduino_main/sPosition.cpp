#include "Arduino.h"
#include "sPosition.h"

sPosition::sPosition(){
  
}

sPosition::~sPosition(){
  
}

void sPosition::handle(){
  
}

int sPosition::handle(byte espMsg){
  return ERROR_STATE;
}


int sPosition::handleWithoutParam(){
  delay(2500); // wait for the buffer on esp to be cleared
  //TODO: send its current position
  Serial.write(B10001110);  //FAKE! position 3
  //if interrupted return error
  //else
  return WAIT_STATE;
}
