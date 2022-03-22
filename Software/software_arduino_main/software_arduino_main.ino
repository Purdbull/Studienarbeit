#include "StateMaschine.h"
StateMaschine* handler;

void setup(){
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  handler = new StateMaschine;
}

void loop() {
  handler->handle();
  delay(200);
}
