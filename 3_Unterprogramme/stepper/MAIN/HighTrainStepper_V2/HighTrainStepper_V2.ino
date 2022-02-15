/*HighTrainStepper Script
   Bantle & Knapp Copyright
   V2 - 15-02-2022
   globale Vars
*/

#define dir 3
#define clk 2
#define en 10
#define m0 4
#define m1 5



int currVelo = 0;


ISR(TIMER1_COMPA_vect) { //Timer1 interrupt. Schaltet Pin 8 um.
  // Weitere Infos auf: https://www.mikrocontroller.net/articles/AVR-Tutorial:_Timer
  digitalWrite(clk, !(digitalRead(clk))); // Aufruffrequenz maximal: 2.604 Khz
  //Frequenz an Pin 8(Hz) = (Arduino clock speed 16,000,000Hz) / (prescaler * (compare match register + 1)) / 2
}

void setup() {
  Serial.begin(9600);
  pinMode(clk, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(en, OUTPUT);
  pinMode(m0, OUTPUT);
  pinMode(m1, OUTPUT);

  //digitalWrite(en, LOW);

  initInterrupts();
}

void loop() { // Hauptschleife - abfragen des Potentiometers

  linear(50, 90);
  delay(5000);
  linear(80, 80);
  delay(5000);
  linear(0, 90);
  delay(5000);
  linear(20, 70);
  delay(5000);

}


void linear(int y, int a) {
  int t = map(a, 0, 100, 500, 10); //Map from a[%] to t[ms]
  int x = currVelo;

  if (x == 0) {
    startVelo(y);
  }

  setMode(1);

  if (x < y) //accelerate
  {
    Serial.println("---> Accelerate from " + String(x) + "% to " + String(y) + "%" );
    for (int i = x; i <= y; i++) {
      setVelo(i);
      delay(t);
      Serial.println(String(i) + "%");
    }
  }


  if (x > y) //deccelarate
  {
    Serial.println("--->Deccelearte from " + String(x) + "% to " + String(y) + " %");
    for (int i = x; i >= y; i--) {
      setVelo(i);
      delay(t);
      Serial.println(String(i) + "%");
    }
  }

  if (y == 0) {
    stopVelo();
  }

  setVelo(y);
}


void startVelo(int y) {
  Serial.println("---->Motor start up");

  setDirection(y); 
  setMode(4);
  delay(3000);
  setMode(2);
  delay(2000);
}


void stopVelo() {
  setMode(2);
  delay(2000);
  setMode(4);
  delay(3000);
  setMode(0);

}

void emergencyBrake() {
  setVelo(0);

}

void setVelo(int velo) {
  setDirection(velo);
  velo = abs(velo);
  int a = map(velo, 100, 0, 31, 130);
  cli();
  OCR1A = a;
  sei();
  currVelo = velo;

}

void initInterrupts() {
  cli();                                //stoppe alle Interrupts
  TCCR1A = 0;                           // set entire TCCR1A register to 0 TCCR - Timer/Counter Control Register
  TCCR1B = 0;                           // Setze Timer/Counter Control Register TCCR1B auf 0
  TCCR1B |= (1 << WGM12);               // Schalte Clear Timer on Compare (CTC) Modus ein
  // TCCR1B |= (1 << CS12) | (1 << CS10);  // Setze CS10 und CS12 Bit auf 1 für den 1024 Prescaler. Maximalfrequenz: 7.812 Khz
  TCCR1B |= (1 << CS12);                 // Setze CS12 Bit auf 1 für den 256 Prescaler.
  TCNT1  = 0;                           // Initialisiere Zähler/Zeitgeber Register Wert auf 0
  OCR1A = 130;//  Aufruffrequenz Timer 1  241 Hz * 2
  TIMSK1 |= (1 << OCIE1A); // Erlaube Timer compare interrupt TIMSK - Timer/Counter Interrupt Mask Register
  sei();//allow interrupts

}

void setMode(int mode) {
  //keep in mind: enable negative logic!
  //full step
  if (mode == 1) {
    digitalWrite(en, 0);
    digitalWrite(m0, 0);
    digitalWrite(m1, 0);
  }

  //half step
  else if (mode == 2) {
    digitalWrite(en, 0);
    digitalWrite(m0, 1);
    digitalWrite(m1, 0);
  }

  //micro step
  else if (mode == 4) {
    digitalWrite(en, 0);
    digitalWrite(m0, 0);
    digitalWrite(m1, 1);
  }

  //disable the motor
  else if (mode == 0) {
    digitalWrite(en, 1);
  }

  if (mode != 0) {
    Serial.println("Mode " + String(mode) + " ativated");
  }

  else {
    Serial.println("------------Motor disabled----------");
  }

}

void setDirection(int velo) {
  if (velo > 0) {
    digitalWrite(dir, 1);

  }

  if (velo < 0) {
    digitalWrite(dir, 0);

  }

  else {
    return;
    //stopMotor!
  }

}



//
