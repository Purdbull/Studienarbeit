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

  
  handler =  new Drivehandler(3, 0, &highTrainStepper);
  handler->drive();
  delay(500);
  delete(handler);
      
}


void loop() {


}
