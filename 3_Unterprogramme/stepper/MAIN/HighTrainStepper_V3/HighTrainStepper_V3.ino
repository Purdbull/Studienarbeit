/*HighTrainStepper Script
   Bantle & Knapp Copyright
   V3 - March 2022
*/

// PinOut
#define dir 3
#define clk 2
#define enbl 10
#define m0 4
#define m1 5
#define led 9

// Min and Max values for timer compare Register OCR1A
#define Max  5500
#define Min 990

//Min and Max Values for acceleration (additional prescaler with modulo)
#define aMax 20
#define aMin 4

int y = Max; //target speed
int k; //counter for ISR Prescaler, Iportant: LONG (!), overflow causes acc. stop
int a; //accelecaration (modulo)
bool yDone = false;
int s;

//-------------setup---------------
void setup() {
  Serial.begin(9600);
  pinMode(clk, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(enbl, OUTPUT);
  pinMode(m0, OUTPUT);
  pinMode(m1, OUTPUT);
  pinMode(led, OUTPUT);
  initInterrupts();

}


//------------functions----------

//-->driving<----
void linear(int s, int b = 40) {
  //s = newSpeed, b = acceleration

  mode(0); //enable motor
    
  if (y != s) {
    setDir(s); 
    if (y == 0) {
      // Motor StartUp
      stepMode(4);
      delay(1000);
      stepMode(2);
      delay(1000);
    }
    y = map(s, 0, 100, Max, Min);
    Serial.println("---->Acc./ Dec. to " + String(s) + " %<---");

  }

  if (a != b) {
    a = map(b, 0, 100, aMax, aMin);
  }


}

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
  TCCR1B |=  (1 << CS11);                 // CS11 & CS01 für 64 Prescaler.
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
  linear(100);
  delay(12000);
  mode(3);
  delay(10000);
  linear(100, 100);
  delay(5000);
  mode(1);
  delay(5000);





}
