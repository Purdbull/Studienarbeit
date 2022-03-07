#include "State.h"
#include "IdleState.h"
#include "StateMashine.h"
#define LED 2
StateMashine handler;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  handler.handle(B10001100);
  handler.handle("hi");
  handler.handle(B00010010);
  handler.handle(B00001011);
}
void loop() {
  
}
