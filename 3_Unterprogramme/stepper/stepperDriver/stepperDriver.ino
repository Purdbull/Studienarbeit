const int dirPin = 2;
const int stp = 1;
const int stepsPerRevolution = 200;
const int M0 = 10;
const int M1 = 11;
const int mode = 2;
const int rpm = 320;
const double r = 0.02;
bool debug = false;

/*
    0 = full step
    1 = half step
    2 = 8 microSteps/ Step
    3 = 16 microSteps/ Step
*/


//#########################SETUP#################
void setup() {
  pinMode(stp, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  if (debug) {
    Serial.begin(9600);
  }

  setMode(mode);

}

  

//###########################MAIN###############
void loop() {
  //HzToV(3.5, true);
  //continuosHz(3.5, true); //max 3.5
  continuosD(5000, false);


}

//#########################FUNCTIONS#############



//-----------Turning functions---------

double continuosD(double d, bool debug) //d in µs
{
  digitalWrite(stp, 0);
  delayMicroseconds(d);
  digitalWrite(stp, 1);
  delayMicroseconds(d);

  if (debug) {
    Serial.print("continuos D mit D=");
    Serial.println(d);
  }

}

double continuosHz (double hz, bool debug)
{
  int d = HzToD(hz, debug);

  if (debug) {
    Serial.print("continuos Hz mit D von ...");
  }
  continuosD(d, false);

}


//----------convertions------------
int HzToD(double hz, bool debug) {
  double T = 1.0 / hz; //Zeit pro Umdrehung
  double d_s = T / (200.0 * 2.0); //Zeit je Step (on/off)
  d_s = d_s * 1E6; //--> µs
  int d = d_s; //conversion to int

  if (debug) {
    Serial.print("HzToD, D=");
    Serial.println(d);
  }
  return d;
}

double HzToV(double hz, bool debug) {
  double v = hz * r;
  if (debug) {
    Serial.print("V =");
    Serial.println(v);
  }
  return v;

}

//------------modes------------------------

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

//-------------------------END----------
//
//double rpmToD(int rpm) {
//  //function converts rpm to T for PWM
//  double u_s = rpm / 60; //turns per second
//  double d = 1 / (u_s* 2);
//  d = d*10E-6;
//  return d;
//}
//
//double rpmToMs(int rpm) {
//  double u_s = rpm/60;
//  double m_s = u_s*r;
//  return m_s;
//
//}
//
//double msToD (int m_s){
//  double u_s = m_s/r;
//  double d = 1/(u_s*2);
//  d = d*10E-6;
//  Serial.println(d);
//  return d;
//
//}
//
//void continuos_ms(int m_s) {
//  double d = msToD(m_s);
//  digitalWrite(stepPin, HIGH);
//  delayMicroseconds(d);
//  digitalWrite(stepPin, LOW);
//  delayMicroseconds(d);
//}
