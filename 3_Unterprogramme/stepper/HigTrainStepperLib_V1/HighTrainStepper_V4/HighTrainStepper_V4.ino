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
  stepper -> linear(10,70); 


}

ISR(TIMER1_COMPA_vect) { //Timer1 Interrupt Service Routine
  stepper -> isr();
}



void loop() {
  stepper -> linear(40,50); 
  delay(5000); 
  stepper -> linear(60,50); 
  delay(5000); 
  
  
}
