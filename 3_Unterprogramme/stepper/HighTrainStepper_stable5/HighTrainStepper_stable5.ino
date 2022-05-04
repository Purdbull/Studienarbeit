/*HighTrainStepper Script
   Bantle & Knapp Copyright
   V3 - March 2022

   Changes: 
   stopModes implemented
*/
#include "HighTrainStepper.h"

Stepper* stepper = new Stepper();



//-------------setup---------------
void setup() {
  Serial.begin(9600);
  stepper ->  initInterrupts(); 


}


//-----------------ISR-----------------

ISR(TIMER1_COMPA_vect) { //Timer1 Interrupt Service Routine
  stepper -> isr();

}

//-------------main--------------
void loop() {
  
  
  //stopBackwards
  stepper -> linear(40);
  delay(7000);
  stepper -> linear(-50, 100);
  delay(8000);
  stepper -> linear(80,100);
  delay(7000); 
  stepper ->stopMode(2); 
  delay(3000); 

}


  /*
  
  //stopBackwards
  delay(7000);
  stepper -> linear(100);
  delay(7000);
  stepper -> linear(-20, 100);
  delay(7000);
  stepper -> stopMode(1);
  delay(7000);
  stepper -> linear(-60);
*/

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
