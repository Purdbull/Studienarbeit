#include "Arduino.h"
#include "sDrive.h"
#include "Drivehandler.h"
#include "EEPROM.h"

sDrive::sDrive(int pos, Stepper* ptr){
  int currentPos = (int)EEPROM.read(0);
  this->drivehandler = new Drivehandler(currentPos, pos, ptr);
}

sDrive::~sDrive(){
  delete(this->drivehandler);
}

void sDrive::handle(){
  this->drivehandler->drive();
}

int sDrive::handleWithoutParam(){
  this->drivehandler->drive();
  return IDLE_STATE;
  //if something crashes
  return ERROR_STATE;
}

int sDrive::handle(byte espMsg){
  return ERROR_STATE;
}
