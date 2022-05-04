#include "Drivehandler.h"


Stepper* highTrainStepper = new Stepper();

Drivehandler* handler = new Drivehandler(3,2, highTrainStepper);
void setup(){
  Serial.begin(9600);
  highTrainStepper->initInterrupts();
  delay(1000);
  handler->drive();
  delay(2000);
delete(handler);
handler = new Drivehandler(3,4, highTrainStepper);
handler->drive();
}

ISR(TIMER1_COMPA_vect) { //Timer1 Interrupt Service Routine
  highTrainStepper -> isr();
}

void loop(){


}
