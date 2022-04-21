#include <Arduino.h>
#include "HighTrainStepper.h"

Stepper::Stepper() {
  pinMode(CLK, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(ENBL, OUTPUT);
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(LED, OUTPUT);

  // Min and Max values for timer compare Register OCR1A
#define MAXVAL 5500 //max register value (lowest clock speed)
#define MINVAL 990 //min register value (highest clock speed)

  //Min and Max Values for acceleration (additional prescaler with modulo)
#define MAXACC 20
#define MINACC 4

  targetRegVal = MAXVAL;
  Stepper::dis();

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
  digitalWrite(CLK, !(digitalRead(CLK)));
  count++;

  //accelerate
  if (OCR1A > targetRegVal && count >= acc) {
    cli();
    OCR1A = OCR1A - 10;
    sei();
    count = 0;
  }

  //decelerate
  if (OCR1A < targetRegVal && count >= acc) {
    cli();
    OCR1A = OCR1A + 10;
    sei();
    count = 0;
  }

  //check target achievement (+offstet)
  if (abs(OCR1A - targetRegVal) <= 10) {
    OCR1A = targetRegVal;
    accDone = true;
    digitalWrite(LED, 1);
  }

  else {
    accDone = false;
    digitalWrite(LED, 0);
  }

}

void Stepper::linear(int targetSpeed, int targetAcc) {

  //map acc and speed
  int _targetRegVal = map(abs(targetSpeed), 0, 100, MAXVAL, MINVAL);
  int _acc = map(targetAcc, 0, 100, MAXACC, MINACC);

  //setDirection
  Stepper::setDir(targetSpeed);

  //check startup requirement
  if (OCR1A == MAXVAL) {
    Serial.println("-->startup<----");
    Stepper::stepMode(4);
    delay(1000);
    Stepper::stepMode(2);
    delay(1000);
  }


  //set Register Value
  if (_targetRegVal != targetRegVal) {
    //Stepper::setDir(targetSpeed);
    targetRegVal = _targetRegVal;
    Serial.println("---->Acc./ Dec. to " + String(targetSpeed) + " %<---");
  }

  //set acceleration
  if (acc != _acc) {
    acc = _acc;
    Serial.println("ACC=" + String(targetAcc) + " %<--- " + String(acc) );
  }
}




// -------------------->Beahviourfunctions
void Stepper::en() {
  digitalWrite(ENBL, 1);
  Serial.println("enable");
}

void Stepper::dis() {
  digitalWrite(ENBL, 0);
  Serial.println("disable");
}

void Stepper::setDir(int targetSpeed) {
  if (targetSpeed < 0) {
    digitalWrite(DIR, 1);
  }

  if (targetSpeed > 0) {
    digitalWrite(DIR, 0);
  }

  if (targetSpeed * OCR1A < 0) {
    //illegal, error!
    return;
  }
}

void Stepper::stepMode(int mode) {
  //keep in mind: enable negative logic!

  //enable motor
  Stepper::en();

  //full step
  if (mode == 1) {
    digitalWrite(M0, 0);
    digitalWrite(M1, 0);
  }

  //half step
  else if (mode == 2) {
    digitalWrite(M0, 1);
    digitalWrite(M1, 0);
    Serial.println("halfStep");
  }

  //micro step
  else if (mode == 4) {
    digitalWrite(M0, 0);
    digitalWrite(M1, 1);
    Serial.println("quarterStep");
  }
}

void Stepper::stopMode(int n) {
  //idleMode
  if (n == 0) {
    Stepper::stepMode(1);
  }

  //emergencyStopMode
  if (n == 1) {
    Serial.println("---->EmergencyStop<----");
    Stepper::linear(0, 100);
    delay(1);
    while (!accDone) {
      delay(1);
    }
    Stepper::dis();
  }

  //stopMode
  if (n == 2) {
    Serial.println("---->Stop<----");
    Stepper::linear(0, 50);
    delay(1);
    while (!accDone) {
      delay(1);
    }
    Stepper::stepMode(2);
    delay(2000);
    Stepper::stepMode(4);
    delay(1500);
    Stepper::dis();
  }

  // stopInStationMode
  if (n == 3) {
    Serial.println("---->StopInStation<----");
    Stepper::linear(0, 50);
    delay(1);
    while (!accDone) {
      delay(1);
    }
    Stepper::stepMode(4);
  }

  // disableMotor
  if (n == 4) {
    Stepper::dis();
  }
}
