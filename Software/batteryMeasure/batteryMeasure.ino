#define PIN_CELL_ONE  A1
#define PIN_CELL_TWO  A0
#define PIN_BATTERY   4

int cellOneMeasures[50];
int cellTwoMeasures[50];

int count = 0;


float cellOneVoltage = 0.0;
float cellTwoVoltage = 0.0;

void setup() {
  pinMode(PIN_BATTERY, OUTPUT);
  pinMode(PIN_CELL_ONE, INPUT);
  pinMode(PIN_CELL_TWO, INPUT);

  Serial.begin(9600);

  for (int i = 0; i < 50; i++) {
    cellOneMeasures[i]; analogRead(PIN_CELL_ONE);
    cellTwoMeasures[i]; analogRead(PIN_CELL_TWO);
  }
}

void updateVoltageArrays(){
  if (count == 50) {
    count = 0;
  }
  cellOneMeasures[count] = analogRead(PIN_CELL_ONE);
  cellTwoMeasures[count] = analogRead(PIN_CELL_TWO);
}

float getCellOneVoltage(){
  updateVoltageArrays();
  float result = 0;
  for (int i = 0; i < 50; i++) {
    result += cellOneMeasures[i];
  }
  result = (((result / 50.0) * 5.0) / 1024.0); //result = actual voltage
  return result;
}

float getCellTwoVoltage(){
  updateVoltageArrays();
  float result = 0;
  for (int i = 0; i < 50; i++) {
    result += cellTwoMeasures[i];
  }
  result = (((result / 50.0) * 5.0) / 1024.0)*2; //result = actual voltage
  result = result-getCellOneVoltage();
  return result;
}

void setVoltageValues(){
  cellOneVoltage = getCellOneVoltage();
  cellTwoVoltage = getCellTwoVoltage();
}

float getCellOneInPercent() {
  setVoltageValues();
  float result = cellOneVoltage;
  result -= 3.7;
  if (result <= 0) {
    return 0.0;
  }
  if (result >= 0.5) {
    return 100.0;
  }

  return result * 200; //now its in % because 0,1 = 20%
}

float getCellTwoInPercent() {
  setVoltageValues();
  float result = cellTwoVoltage;
  result -= 3.7;
  if (result <= 0) {
    return 0.0;
  }
  if (result >= 0.5) {
    return 100.0;
  }

  return result * 200; //now its in 1-100% because 0,1 = 20%
}

void loop() {

}
