/*HighTrainStepper Script
   Bantle & Knapp Copyright
   V1 - 10-02-2022
*/

#define dir 3
#define clk 2
#define en 6
#define m0 4
#define m1 5


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
  setVelo(50);
  digitalWrite(dir, 0);


}

void loop() { // Hauptschleife - Abfragen des Potentiometers

  linear(20, 75, 90);
  delay(10000);
  emergencyBrake();
  delay(5000);  
}


void linear(int x, int y, int acc) {
  
  int t = map(acc,0,100,500,10); //Map from acc[%] to t[ms]
  if (x < y) //acccelerate
  {
    Serial.println("---> Accelerate from " + String(x) + "% to " + String(y) + "%" );
    for (int i = x; i <= y; i++) {
      setVelo(i);
      delay(t);
      Serial.println(String(i) + "%");
    }
  }


  if (x > y) //decelerate
  {
    Serial.println("--->Decelerate from " + String(x) + "% to " + String(y) + " %");
    for (int i = x; i >= y; i--) {
      setVelo(i);
      delay(t);
      Serial.println(String(i) + "%");
    }
  }

  setVelo(y);
}


void emergencyBrake(){
  setVelo(0); 


  
}

void setVelo(int velo) {
  setDirection(velo);
  velo = abs(velo);
  int a = map(velo, 100, 0, 31, 130);
  cli();
  OCR1A = a;
  sei();

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
