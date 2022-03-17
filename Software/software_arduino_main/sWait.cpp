#include "Arduino.h"
#include "sWait.h"

sWait::sWait(){
}

void sWait::handle(){
  
}

int sWait::handle(byte espMsg){
  return ERROR_STATE;
}

int sWait::handleWithoutParam(){
  int _time = millis();
  while(Serial.available() == 0){
    if((millis()-_time)>5000){
      return ERROR_STATE;
    }
  }
  //TODO evaluate position. if wrong send dec
  //else this->driveToPosition = pos &
  return DRIVE_STATE;
}
