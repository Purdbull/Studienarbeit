#include "Drivehandler.h"


Stepper* highTrainStepper = new Stepper();

Drivehandler* handler = new Drivehandler(5,2, highTrainStepper);
void setup(){
  Serial.begin(9600);
  highTrainStepper->initInterrupts();
  delay(1000);
  handler->drive();
}

ISR(TIMER1_COMPA_vect) { //Timer1 Interrupt Service Routine
  highTrainStepper -> isr();

}

void loop(){
delay(2000);
delete(handler);
handler = new Drivehandler(2,6, highTrainStepper);
handler->drive();

delay(2000);
delete(handler);
handler = new Drivehandler(6,5, highTrainStepper);
handler->drive();

delay(2000);
delete(handler);
handler = new Drivehandler(5,2, highTrainStepper);
handler->drive();
}
