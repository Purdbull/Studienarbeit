const int dirPin = 2;
const int stepPin = 1;
const int stepsPerRevolution = 200;
const int M0 = 10;
const int M1 = 11;
const int mode = 0;
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

  for (int i = 0; i <= 4; i++) {
    turn(t*i);
  }

   for (int i = 4; i >= 0; i--) {
    turn(t*i);
  }

}

void continuos(int t) {
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(toT(t));
  digitalWrite(stepPin, LOW);
  delayMicroseconds(toT(t));
}

void turn(int t) {
  for (int i = 0; i <= stepsPerRevolution; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(toT(t));
    digitalWrite(stepPin, LOW);
    delayMicroseconds(toT(t));
  }

}


int toT(int t) {
  int rpm;
  rpm = t;
  return rpm;
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
