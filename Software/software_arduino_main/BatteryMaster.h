#include "Arduino.h"

#ifndef BatteryMaster_h
#define BatteryMaster_h

class BatteryMaster {
  public:
    BatteryMaster(int, int, int);

    int count;
    int cellOneMeasures[50];
    int cellTwoMeasures[50];
    int PIN_CELL_ONE;
    int PIN_CELL_TWO;
    int ACTIVATOR_PIN;

    float cellOneVoltage;
    float cellTwoVoltage;

    void updateVoltageArrays();
    float getCellOneVoltage();
    float getCellTwoVoltage();
    void setVoltageValues();
    float getCellOneInPercent();
    float getCellTwoInPercent();
};

#endif
