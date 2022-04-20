#include <Arduino.h>
#include "HighTrainStepper.h"

Stepper::Stepper()
{
  pinMode(CLK, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(ENBL, OUTPUT);
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(LED, OUTPUT);
  yDone = false;
  Stepper::initInterrupts();

}
Stepper::~Stepper() {
  //clear Interrupts --> schauen!
}

//------------->Interrupts<----------------

void Stepper::initInterrupts() {
  cli();                                //clear local interrupt flag
  TCCR1A = 0;                           // set entire TCCR1A register to 0 TCCR - Timer/Counter Control Register
  TCCR1B = 0;                           // Setze Timer/Counter Control Register TCCR1B auf 0
  TCCR1B |= (1 << WGM12);               // Schalte Clear Timer on Compare (CTC) Modus ein
  //TCCR1B |= (1 << CS12) | (1 << CS10);  // Setze CS10 und CS12 Bit auf 1 für den 1024 Prescaler. Maximalfrequenz: 7.812 Khz
  TCCR1B |=  (1 << CS11);                 // CS11 für den 8 Bit Prescaler
  TCNT1  = 0;                           // Initialisiere Zähler/Zeitgeber Register Wert auf 0
  OCR1A = MAX;//  Aufruffrequenz Timer 1  241 Hz * 2
  TIMSK1 |= (1 << OCIE1A); // Erlaube Timer compare interrupt TIMSK - Timer/Counter Interrupt Mask Register
  sei();//allow interrupts
}

void Stepper::isr() {
  //Timer1 Interrupt Service Routine
  digitalWrite(CLK, !(digitalRead(CLK)));
  k++;
  if (OCR1A > y && k >= a) {
    //accelerate
    cli();
    OCR1A = OCR1A - 10;
    sei();
    k = 0;

  }

  if (OCR1A < y && k >= a) {
    //decelerate
    cli();
    OCR1A = OCR1A + 10;
    sei();
    k = 0;

  }


  if (abs(OCR1A - y) <= 10) {
    OCR1A = y;
    yDone = true;
    digitalWrite(LED, 0);
  }

  else {
    yDone = false;
    digitalWrite(LED, 1);
  }



}

//------------->DRIVING<----------------


void Stepper::linear(int s, int b = 40) {
  //s = newSpeed -->y, b = acceleration -->a

  //map s to new y
  int y_new = map(abs(s), 0, 100, MAX, MIN); //<-- VZ beachten!


  if (abs(s) > 0) {
    Stepper::mode(0); //enable motor
  }


  if (y_new != y) {
    Stepper::setDir(s);
    if (y == MAX) {
      Serial.println("-->startup<----");
      // Motor StartUp
      Stepper::stepMode(4);
      delay(1000);
      Stepper::stepMode(2);
      delay(1000);
    }
    y = y_new; //set new global y
    Serial.println("---->Acc./ Dec. to " + String(s) + " %<---");

  }

  // map acceleration to global a
  a = map(b, 0, 100, A_MAX, A_MIN);


}

//------------->MODES<----------------

void Stepper:: mode(int n) {
  //idleMode
  if (n == 0) {
    en();
    Stepper::stepMode(1);
  }

  //emergencyStopMode
  if (n == 1) {
    Serial.println("---->EmergencyStop<----");
    Stepper::linear(0, 100);
    delay(1);
    while (!yDone) {
      delay(1);
    }
    dis();
  }

  //stopMode
  if (n == 2) {
    Serial.println("---->Stop<----");
    Stepper::linear(0);
    delay(1);
    while (!yDone) {
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
    Stepper::linear(0);
    delay(1);
    while (!yDone) {
      delay(1);
    }
    Stepper::stepMode(4);
  }

  // disableMotor

  if (n == 4) {
    Stepper::dis();
  }
}

void Stepper::stepMode(int mode) {
  //keep in mind: enable negative logic!
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

void Stepper::en() {
  digitalWrite(ENBL, 1);
}

void Stepper::dis() {
  {
    digitalWrite(ENBL, 0);
    Serial.println("disabled");
  }
}

void Stepper::setDir(int s) {
  if (s < 0) {
    digitalWrite(DIR, 1);
  }

  if (s > 0) {
    digitalWrite(DIR, 0);
  }

  if (s * y < 0) {
    //illegal, error!
    return;
  }

}
