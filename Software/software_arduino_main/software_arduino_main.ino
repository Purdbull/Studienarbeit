#include "StateMaschine.h"
#include "Drivehandler.h"
#include "EEPROM.h"
#include "Arduino.h"

#include "HighTrainStepper.h"

Stepper highTrainStepper = Stepper();
StateMaschine* handler;

ISR(TIMER1_COMPA_vect) { //Timer1 Interrupt Service Routine
  highTrainStepper.isr();
}


void setup() {
  Serial.begin(9600);
  
highTrainStepper.initInterrupts();
  pinMode(13, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
delay(5000);
handler = new StateMaschine(&highTrainStepper);
}



void loop() {
  handler->handle();
  delay(200);
}
