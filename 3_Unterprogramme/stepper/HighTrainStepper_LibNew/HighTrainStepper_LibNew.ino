/*HighTrainStepper Script
   Bantle & Knapp Copyright
   V3 - March 2022
*/
#include <HCSR04.h>
#include "HighTrainStepper.h"

Stepper* stepper = new Stepper();


void setup() {
  Serial.begin(9600);

}


//-----------------ISR-----------------

ISR(TIMER1_COMPA_vect) { //Timer1 Interrupt Service Routine
  stepper -> isr();

}

//-------------main--------------
void loop() {
  stepper -> linear(70);
  delay(7000);
  stepper -> linear(-70);
  delay(7000);
  stepper -> stopMode(1);
  delay(6000);
  stepper -> linear(-50);
  delay(5000);
  stepper -> stopMode(2);
  delay(7000);
  stepper -> linear(50);
  delay(8000);
  stepper -> stopMode(3);
  delay(6000);
  stepper -> stopMode(4);
  delay(2000);
  stepper -> linear(-100);
  delay(8000);
  stepper -> stopMode(2);
  delay(7000);








}
/*
  stepper -> stepMode(2);
  stepper -> linear(-50, 20);
  delay(5000);
  stepper -> stepMode(4);

  stepper -> linear(-40, 80);
  delay(5000);

  stepper -> stepMode(1);
  stepper -> linear(100, 100);
  delay(5000);
*/

/*
  delay(5000);
  stepper -> stopMode(1);
  delay(4000);
  stepper -> stopMode(2);
  delay(4000);
  stepper -> stopMode(3);
  delay(4000);
  stepper -> stopMode(4);
  delay(4000);
*/
