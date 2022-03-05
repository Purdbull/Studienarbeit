#include "State.h"
#include "IdleState.h"
#include "StateMashine.h"
#define LED 2
StateMashine handler;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

}
void loop() {
  
}
