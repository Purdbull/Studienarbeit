/*HighTrainStepper Script
   Bantle & Knapp Copyright
   V3 - March 2022
*/
#include "Stepper.h"


//-------------setup---------------
void setup() {
  Serial.begin(9600);
  initInterrupts();

}


//------------functions----------

//-->driving<----


//--->modes<----
void mode(int n) {
  //idleMode
  if (n == 0) {
    en();
    stepMode(1);
  }

  //emergencyStopMode
  if (n == 1) {
    Serial.println("---->EmergencyStop<----");
    linear(0, 100);
    delay(1);
    while (!yDone) {
      delay(1);
    }
    dis();
  }

  //stopMode
  if (n == 2) {
    Serial.println("---->Stop<----");
    linear(0);
    delay(1);
    while (!yDone) {
      delay(1);
    }
    stepMode(2);
    delay(2000);
    stepMode(4);
    delay(1500);
    dis();
  }

  // stopInStationMode
  if (n == 3) {
    Serial.println("---->StopInStation<----");
    linear(0);
    delay(1);
    while (!yDone) {
      delay(1);
    }
    stepMode(4);
  }

  // disableMotor

  if (n == 4) {
    dis();
  }
}


void stepMode(int mode) {
  //keep in mind: enable negative logic!
  //full step
  if (mode == 1) {
    digitalWrite(m0, 0);
    digitalWrite(m1, 0);
  }

  //half step
  else if (mode == 2) {
    digitalWrite(m0, 1);
    digitalWrite(m1, 0);
    Serial.println("halfStep");
  }

  //micro step
  else if (mode == 4) {
    digitalWrite(m0, 0);
    digitalWrite(m1, 1);
    Serial.println("quarterStep");

  }

}

//-->dis/en/dir<----
void en() {
  digitalWrite(enbl, 1);
}

void dis() {
  digitalWrite(enbl, 0);
  Serial.println("disabled");
}

void setDir(int s) {
  if (s < 0) {
    digitalWrite(dir, 1);
  }

  if (s > 0) {
    digitalWrite(dir, 0);
  }

  if (s * y < 0) {
    //illegal, error!
    return;
  }

}


//---->Interrupts<----
void initInterrupts() {
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


//-----------------ISR-----------------

ISR(TIMER1_COMPA_vect) { //Timer1 Interrupt Service Routine
  digitalWrite(clk, !(digitalRead(clk)));
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
    digitalWrite(led, 1);
  }

  else {
    yDone = false;
    digitalWrite(led, 0);
  }


}


//-------------main--------------
void loop() {
  /*linear(100);
    delay(12000);

    mode(2);
  */
  linear(-40);
  delay(5000);
  mode(2);
  delay(4000);
  linear(40);
  delay(10000);

}
