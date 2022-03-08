#include "State.h"
#include "IdleState.h"
#include "StateMashine.h"
#define LED 2
StateMashine handler;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  handler.handle(B10001100); //Akkustand mit richtigem Tail
  handler.handle(B00001100); //Akkustand mit falschem Tail
  
  handler.handle("hi");
  handler.handle(B00010010);
  handler.handle(B00000111); //akzeptierter fahrbefehl

  handler.handle("hi");
  handler.handle(B00011010);
  handler.handle(B00001011); //abgelehnter fahrbefehl
}
void loop() {
  
}
