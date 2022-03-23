#include "Arduino.h"
#include "BatteryMaster.h"

BatteryMaster::BatteryMaster(int cellOnePin, int cellTwoPin, int activatorPin) {
  pinMode(cellOnePin, INPUT);
  pinMode(cellTwoPin, INPUT);
  pinMode(activatorPin, OUTPUT);

  BatteryMaster::PIN_CELL_ONE = cellOnePin;
  BatteryMaster::PIN_CELL_TWO = cellTwoPin;
  BatteryMaster::ACTIVATOR_PIN = activatorPin;


  BatteryMaster::cellOneVoltage = 0.0;
  BatteryMaster::cellTwoVoltage = 0.0;

  BatteryMaster::count = 0;

  for (int i = 0; i < 50; i++) {
    BatteryMaster::cellOneMeasures[i]; analogRead(BatteryMaster::PIN_CELL_ONE);
    BatteryMaster::cellTwoMeasures[i]; analogRead(BatteryMaster::PIN_CELL_TWO);
  }
}

void BatteryMaster::updateVoltageArrays() {
  if (BatteryMaster::count == 50) {
    BatteryMaster::count = 0;
  }
  BatteryMaster::cellOneMeasures[count] = analogRead(BatteryMaster::PIN_CELL_ONE);
  BatteryMaster::cellTwoMeasures[count] = analogRead(BatteryMaster::PIN_CELL_TWO);
}


float BatteryMaster::getCellOneVoltage() {
  BatteryMaster::updateVoltageArrays();
  float result = 0;
  for (int i = 0; i < 50; i++) {
    result += BatteryMaster::cellOneMeasures[i];
  }
  result = (((result / 50.0) * 5.0) / 1024.0); //result = actual voltage
  return result;
}

float BatteryMaster::getCellTwoVoltage() {
  BatteryMaster::updateVoltageArrays();
  float result = 0;
  for (int i = 0; i < 50; i++) {
    result += BatteryMaster::cellTwoMeasures[i];
  }
  result = (((result / 50.0) * 5.0) / 1024.0) * 2; //result = actual voltage
  result = result - BatteryMaster::getCellOneVoltage();
  return result;
}

void BatteryMaster::setVoltageValues() {
  BatteryMaster::cellOneVoltage = BatteryMaster::getCellOneVoltage();
  BatteryMaster::cellTwoVoltage = BatteryMaster::getCellTwoVoltage();
}

float BatteryMaster::getCellOneInPercent() {
  BatteryMaster::setVoltageValues();
  float result = BatteryMaster::cellOneVoltage;
  result -= 3.7;
  if (result <= 0) {
    return 0.0;
  }
  if (result >= 0.5) {
    return 100.0;
  }

  return result * 200; //now its in % because 0,1 = 20%
}

float BatteryMaster::getCellTwoInPercent() {
  BatteryMaster::setVoltageValues();
  float result = BatteryMaster::cellTwoVoltage;
  result -= 3.7;
  if (result <= 0) {
    return 0.0;
  }
  if (result >= 0.5) {
    return 100.0;
  }

  return result * 200; //now its in 1-100% because 0,1 = 20%
}
