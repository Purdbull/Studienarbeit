#include "StateMaschine.h"
#include "Drivehandler.h"
#include "EEPROM.h"

Stepper* highTrainStepper = new Stepper();
StateMaschine* handler = new StateMaschine(highTrainStepper);



void setup(){
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  highTrainStepper->initInterrupts();
  delay(1000);
}

ISR(TIMER1_COMPA_vect) { //Timer1 Interrupt Service Routine
  highTrainStepper->isr();
}

void loop() {
  handler->handle();
  delay(200);
}
