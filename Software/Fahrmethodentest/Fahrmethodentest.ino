#include "Drivehandler.h"


#include "HighTrainStepper.h"
Stepper highTrainStepper = Stepper();


ISR(TIMER1_COMPA_vect) { //Timer1 Interrupt Service Routine
  highTrainStepper.isr();
}

Drivehandler* handler;
void setup() {
  Serial.begin(9600);
  highTrainStepper.initInterrupts();
  handler =  new Drivehandler(0,2, &highTrainStepper);
  handler->drive();
  delay(2000);
  delete(handler);
  handler = new Drivehandler(3, 4, &highTrainStepper);
  handler->drive();
  delay(2000);
  handler =  new Drivehandler(2,5, &highTrainStepper);
  handler->drive();
  delay(2000);
  delete(handler);
  handler = new Drivehandler(6, 5, &highTrainStepper);
  handler->drive();
  delay(2000);
}


void loop() {


}
