#include "Arduino.h"
#include "sIdle.h"

sIdle::sIdle() {
  batteryMeasure = new BatteryMaster(1, 2, 3); //TODO::right numbers
  jarvis = new Decoder();
}

void sIdle::handle() {

}

void sIdle::sendBattery(float s1, float s2) {
  float s = (s1 + s2) / 2;
  s /= 6.25;
  byte msg = (byte)round(s);
  msg << 2;
  msg = msg & B10000000;
  Serial.write(msg);
}

int sIdle::handle(byte espMsg) {
  if (jarvis->getHeader(espMsg) == HEADER_ASK) {
    return POSITION_STATE;
  }
  return ERROR_STATE;
}

int sIdle::handleWithoutParam() {
  float cell1 = batteryMeasure->getCellOneInPercent();
  float cell2 = batteryMeasure->getCellTwoInPercent();

  if (cell1 < 10.0 | cell2 < 10.0) {
    return CHARGE_STATE;
  }
  else {
    sendBattery(cell1, cell2);
    return IDLE_STATE;
  }
  return ERROR_STATE;
}
