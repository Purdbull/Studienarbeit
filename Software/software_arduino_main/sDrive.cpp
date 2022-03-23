#include "Arduino.h"
#include "sDrive.h"

sDrive::sDrive(int pos){
  this->driveToPosition = pos;
}

sDrive::~sDrive(){
  //todo
}

void sDrive::handle(){
  
}

int sDrive::handleWithoutParam(){
  //todo:drive function!! then
  return IDLE_STATE;
  //if something crashes
  return ERROR_STATE;
}

int sDrive::handle(byte espMsg){
  return ERROR_STATE;
}
