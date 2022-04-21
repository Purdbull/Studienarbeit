const int dirPin = 2;
const int stepPin = 1;
const int stepsPerRevolution = 200;
const int M0 = 10;
const int M1 = 11;
const int mode = 1;
const int t = 350;


/*
    0 = full step
    1 = half step
    2 = 8 microSteps/ Step
    3 = 16 microSteps/ Step
*/

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);

  setMode(mode);

}

void loop() {
  continuos(378, 100); //c
  delay(100);



  continuos(227, 100); //g
  delay(100);
  continuos(200, 100); //a
  delay(100);

  continuos(189, 100); //h
  delay(100);

  continuos(250, 100); //f
  delay(100);

  continuos(250, 100); //f
  delay(100);
  continuos(337, 300); //d
  delay(100);
  continuos(300, 100); //e
  delay(100);
  continuos(189, 100); //h
  delay(100);

  continuos(250, 50); //f
  delay(100);
  continuos(250, 100); //f
  delay(100);
  continuos(337, 100); //d
  delay(100);
  continuos(227, 200); //g
  delay(100);
  continuos(250, 250); //f
  delay(100);
  continuos(337, 100); //d
  delay(100);

  continuos(378, 100); //c
  delay(100);
  continuos(337, 100); //d
  delay(100);

  continuos(200, 500); //a
  delay(100);
}

void continuos(double t, int n) {
  int i = 0;
  while ( i < n) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(toT(t));
    digitalWrite(stepPin, LOW);
    delayMicroseconds(toT(t));
    i++;
  }

}



int toT(int t) {
  int rpm;
  rpm = t;
  return rpm;
}

void turn (int f, int d) {
  double T = 1.0 / f;
  int n = d / T;
  int i = 0;
  while ( i < n) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(T);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(T);

    i++;
  }
}

void setMode(int mode) {
  switch (mode) {
    case 0:
      digitalWrite(M0, 0);
      digitalWrite(M1, 0);
      break;


    case 1:
      digitalWrite(M0, 1);
      digitalWrite(M1, 0);
      break;

    case (2):
      digitalWrite(M0, 0);
      digitalWrite(M1, 1);
      break;


    case (3):
      digitalWrite(M0, 1);
      digitalWrite(M1, 1);
      break;
  }
}
