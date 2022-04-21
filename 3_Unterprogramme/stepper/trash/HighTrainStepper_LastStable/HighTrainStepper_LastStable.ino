/*HighTrainStepper Script
   Bantle & Knapp Copyright
   V3 - March 2022
*/
#include <HCSR04.h>
#include "HighTrainStepper.h"

Stepper* stepper = new Stepper();



//-------------setup---------------
void setup() {
  Serial.begin(9600);

  stepper -> initInterrupts();
  stepper -> en();


}


//-----------------ISR-----------------

ISR(TIMER1_COMPA_vect) { //Timer1 Interrupt Service Routine
  stepper -> isr();

}

//-------------main--------------
void loop() {
  stepper -> linear(70, 30);
  delay(5000);
  stepper -> stepMode(2);
  stepper -> linear(-50, 20);
  delay(5000);
  stepper -> stepMode(4);

  stepper -> linear(-40, 80);
  delay(5000);

}
