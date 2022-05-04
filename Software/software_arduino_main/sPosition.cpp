#include "Arduino.h"
#include "sPosition.h"
#include "EEPROM.h"

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
  delay(2500);
  byte pos = EEPROM.read(0);
  pos  = pos << 2;
  pos = pos | B10000010; //with order mask
  Serial.write(pos);
  //Serial.write(B10001110);  //FAKE! position 3
  //if interrupted return error
  //else
  return WAIT_STATE;
}
