/*HighTrainStepper Script
   Bantle & Knapp Copyright
   V3 - March 2022
*/

// PinOut
#define dir 3
#define clk 2
#define en 10
#define m0 4
#define m1 5

// Min and Max values for timer compare Register OCR1A
#define Max  5500
#define Min 990

//Min and Max Values for acceleration (additional prescaler with modulo)
#define aMax 20
#define aMin 5

int y = Max; //target speed
int k; //counter for ISR Prescaler
int a; //accelecaration (modulo)

bool yDone = false;

//-------------setup---------------
void setup() {
  Serial.begin(9600);
  pinMode(clk, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(en, OUTPUT);
  pinMode(m0, OUTPUT);
  pinMode(m1, OUTPUT);
  initInterrupts();

}

//-------------main--------------
void loop() {
  delay(100); //important Delay after writing new int value while executing ISR

  linear(10);
  delay(6000);

  linear(50);
  delay(5000);

  linear(80);
  delay(5000);

  linear(20);
  delay(5000);

  linear(0, 100);
  delay(7000);

}


//------------functions----------


void linear(int s, int b)
//s = newSpeed, b = acceleration

{

  if (y != s) {
    y = map(s, 0, 100, Max, Min);
    Serial.println("---->Acc./ Dec. to " + String(s) + " %<---");

  }

  if (a != b) {
    a = map(b, 0, 100, aMax, aMin);
  }



}

void linear(int s)
//s = newSpeed, b = acceleration

{

  if (y != s) {

    y = map(s, 0, 100, Max, Min);
    Serial.println("---->Acc./ Dec. to " + String(s) + " %<---");
  }

  if (a != 10) {
    a = map(50, 0, 100, aMax, aMin);
  }



}


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
//---------ISR----------

ISR(TIMER1_COMPA_vect) { //Timer1 Interrupt Service Routine
  digitalWrite(clk, !(digitalRead(clk)));
  k++;

  if (OCR1A > y && k % a == 1) {
    cli();
    OCR1A = OCR1A - 10;
    sei();
  }

  if (OCR1A < y && k % a == 1) {
    cli();
    OCR1A = OCR1A + 10;
    sei();
  }


  if (abs(OCR1A - y) <= 10) {
    OCR1A = y;
  }

  yDone = y == OCR1A;


}
