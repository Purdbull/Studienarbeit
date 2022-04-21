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
  delay(7000);
  stepper -> linear(90);
  delay(7000);
  stepper -> linear(20);
  delay(7000);
  stepper -> linear(90);
}

/*tepper -> linear(70);
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
*/
