#include <Arduino.h>
#include "HighTrainStepper.h"

Stepper::Stepper() {
  pinMode(clk, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(enbl, OUTPUT);
  pinMode(m0, OUTPUT);
  pinMode(m1, OUTPUT);
  pinMode(led, OUTPUT);

  // Min and Max values for timer compare Register OCR1A
#define Max  5500
#define Min 990

  //Min and Max Values for acceleration (additional prescaler with modulo)
#define aMax 20
#define aMin 4

  int targetIr = Max; //target speed
  int counter; //counter for ISR Prescaler,
  int acc; //accelecaration (modulo)
  bool yDone = false;
  int s;

}


void Stepper::initInterrupts() {
  cli();                                //clear local interrupt flag
  TCCR1A = 0;                           // set entire TCCR1A register to 0 TCCR - Timer/Counter Control Register
  TCCR1B = 0;                           // Setze Timer/Counter Control Register TCCR1B auf 0
  TCCR1B |= (1 << WGM12);               // Schalte Clear Timer on Compare (CTC) Modus ein
  //TCCR1B |= (1 << CS12) | (1 << CS10);  // Setze CS10 und CS12 Bit auf 1 für den 1024 Prescaler. Maximalfrequenz: 7.812 Khz
  TCCR1B |=  (1 << CS11);                 // CS11 für den 8 Bit Prescaler
  TCNT1  = 0;                           // Initialisiere Zähler/Zeitgeber Register Wert auf 0
  OCR1A = Max;//  Aufruffrequenz Timer 1  241 Hz * 2
  TIMSK1 |= (1 << OCIE1A); // Erlaube Timer compare interrupt TIMSK - Timer/Counter Interrupt Mask Register
  sei();//allow interrupts

}

void Stepper::isr() {
  digitalWrite(clk, !(digitalRead(clk)));
  if (targetIr != OCR1A) {
    OCR1A = targetIr;
  }
}

void Stepper::linear() {
  targetIr = 5500;
}
