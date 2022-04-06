#include <Arduino.h>
#include "HighTrainStepper.h"


void Stepper::linear(int s, int b = 40) {
  //s = newSpeed -->y, b = acceleration -->a

  //map s to new y
  int y_new = map(abs(s), 0, 100, Max, Min); //<-- VZ beachten!


  if (abs(s) > 0) {
    mode(0); //enable motor
  }


  //check if startup neccessary
  if (y_new != y) {
    setDir(s);
    if (y == Min) {
      // Motor StartUp
      stepMode(4);
      delay(1000);
      stepMode(2);
      delay(1000);
    }
    y = y_new; //set new global y
    Serial.println("---->Acc./ Dec. to " + String(s) + " %<---");

  }

  // map acceleration to global a
  a = map(b, 0, 100, aMax, aMin);


}
