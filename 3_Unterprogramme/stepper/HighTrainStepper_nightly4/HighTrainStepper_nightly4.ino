/*HighTrainStepper Script
   Bantle & Knapp Copyright
   V3 - March 2022

   Changes: 
   startup implemented
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
  stepper -> linear(100);
  delay(7000);
  stepper -> linear(-20, 100);
  delay(7000);
  stepper -> linear(0);
  delay(7000);
  stepper -> linear(-60);

}


/*
  //normalDrive
  delay(7000);
  stepper -> linear(100);
  delay(7000);
  stepper -> linear(20, 100);
  delay(7000);
  stepper -> linear(40);
  delay(7000);
  stepper -> linear(0);
*/

/*
  //bothDirections
  delay(7000);
  stepper -> linear(100);
  delay(7000);
  stepper -> linear(-20, 100);
  delay(7000);
  stepper -> linear(0);
  delay(7000);
  stepper -> linear(-60);
*/
