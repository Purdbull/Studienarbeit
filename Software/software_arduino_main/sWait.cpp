#include "Arduino.h"
#include "sWait.h"

sWait::sWait(){
}

void sWait::handle(){
  
}

int sWait::handle(byte espMsg){
  return ERROR_STATE;
}

void sWait::clearSerialBuffer() {
  char c;
  while (Serial.available()) {
    c = Serial.read();
  }
}

int sWait::handleWithoutParam(){
  int _time = millis();
  while(Serial.available() == 0){
    if((millis()-_time)>10000){
      return ERROR_STATE;
    }
  }
  int pos = 17;
  byte espMsg = Serial.read();
  sWait::clearSerialBuffer();
  if (jarvis->getHeader(espMsg) == HEADER_POSITION){
    pos = jarvis->getBody(espMsg);
  }
  if (pos>=0 && pos <=15){
    this->driveToPosition = pos;
    Serial.write(B10000111); //acc
    return DRIVE_STATE;
  }
  Serial.write(B10001011); //dec
  return ERROR_STATE;
}
