#include "Drivehandler.h"


Stepper* highTrainStepper = new Stepper();

Drivehandler* handler = new Drivehandler(2,5, highTrainStepper);
void setup(){
  
}

ISR(TIMER1_COMPA_vect) { //Timer1 Interrupt Service Routine
  highTrainStepper -> isr();

}

void loop(){
  handler->drive();
}
