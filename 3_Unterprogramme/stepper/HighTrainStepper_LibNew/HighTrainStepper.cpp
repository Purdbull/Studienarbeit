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
#define MAXVAL 5500 //max register value (lowest clock speed)
#define MINVAL 990 //min register value (highest clock speed)

  //Min and Max Values for acceleration (additional prescaler with modulo)
#define MAXACC 20
#define MINACC 4

}


void Stepper::initInterrupts() {
  cli();                                //clear local interrupt flag
  TCCR1A = 0;                           // set entire TCCR1A register to 0 TCCR - Timer/Counter Control Register
  TCCR1B = 0;                           // Setze Timer/Counter Control Register TCCR1B auf 0
  TCCR1B |= (1 << WGM12);               // Schalte Clear Timer on Compare (CTC) Modus ein
  //TCCR1B |= (1 << CS12) | (1 << CS10);  // Setze CS10 und CS12 Bit auf 1 für den 1024 Prescaler. Maximalfrequenz: 7.812 Khz
  TCCR1B |=  (1 << CS11);                 // CS11 für den 8 Bit Prescaler
  TCNT1  = 0;                           // Initialisiere Zähler/Zeitgeber Register Wert auf 0
  OCR1A = MAXVAL;//  Aufruffrequenz Timer 1  241 Hz * 2
  TIMSK1 |= (1 << OCIE1A); // Erlaube Timer compare interrupt TIMSK - Timer/Counter Interrupt Mask Register
  sei();//allow interrupts

}

void Stepper::isr() {
  digitalWrite(clk, !(digitalRead(clk)));
  count++;

  if (OCR1A > targetRegVal && count >= acc) {
    //accelerate

    cli();
    OCR1A = OCR1A - 10;
    sei();
    count = 0;
  }


  if (OCR1A < targetRegVal && count >= acc) {
    //decelerate

    cli();
    OCR1A = OCR1A + 10;
    sei();
    count = 0;
  }

}

void Stepper::linear(int targetSpeed, int targetAcc) {
  int _targetRegVal = map(abs(targetSpeed), 0, 100, MAXVAL, MINVAL);
  int _acc = map(targetAcc, 0, 100, MAXACC, MINACC);

  //set Register Value
  if (_targetRegVal != targetRegVal) {
    targetRegVal = _targetRegVal;
    Serial.println("---->Acc./ Dec. to " + String(targetSpeed) + " %<---");
  }

  //set acceleration
  if (acc != _acc) {
    acc = _acc;
    Serial.println("ACC=" + String(targetAcc) + " %<--- "+ String(acc) );

  }
}

void Stepper::en() {
  digitalWrite(enbl, 1);

}
