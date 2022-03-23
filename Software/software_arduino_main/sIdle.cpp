#include "Arduino.h"
#include "sIdle.h"

sIdle::sIdle() {
  this->batteryMeasure = new BatteryMaster(1,2,3); //TODO::right numbers
  this->jarvis = new Decoder;
  //Serial.print("hellothere");
}

sIdle::~sIdle(){
  delete (this->batteryMeasure);
  delete (this->jarvis);
}

void sIdle::handle() {

}

void sIdle::sendBattery(float s1, float s2) {
  float s = (s1 + s2) / 2;
  s /= 6.25; 
  byte msg = (byte)round(s);
  msg << 2;
  msg = msg | B10000000;
  Serial.write(msg);
  delay(100); //to not fill the other buffer
}

int sIdle::handle(byte espMsg) {
  if (jarvis->getHeader(espMsg) == HEADER_ASK) {
    return POSITION_STATE;
  }
  return ERROR_STATE;
}

int sIdle::handleWithoutParam() {
  float cell1 = this->batteryMeasure->getCellOneInPercent();
  float cell2 = this->batteryMeasure->getCellTwoInPercent();

  if (11.0 < 10.0 | 11.0 < 10.0) { //cell1 cell 2
    return CHARGE_STATE;
  }
  else {
    sIdle::sendBattery(cell1, cell2);
    return IDLE_STATE;
  }
  return ERROR_STATE;
}
