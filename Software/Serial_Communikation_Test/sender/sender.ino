#include "State.h"
#include "IdleState.h"
#include "StateMashine.h"
#define LED 2
StateMashine handler;

void setup() {
  
  //Begin der Seriellen Kommunikation mit 9600 baud 
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  //senden von "Hallo Welt!" über die Serielle Schnittstelle

}
void loop() {
  handler.handle("d");
  handler.handle(B01);
  handler.handle(B01);
}
