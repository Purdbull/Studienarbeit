#include "Arduino.h"
#include "sCharge.h"

sCharge::sCharge(){
  }

void sCharge::handle(){
  
}

int sCharge::handle(byte espMsg){
  return ERROR_STATE;
}

int sCharge::handleWithoutParam(){
  //Todo: drive to position 0 and 
  return OFF_STATE;
  //else
  return ERROR_STATE;
}
