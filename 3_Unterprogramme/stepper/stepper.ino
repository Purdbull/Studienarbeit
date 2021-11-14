// Define pin connections & motor's steps per revolution
//const int dirPin = 2;
const int stepPin = 5;
const int stepsPerRevolution = 200;
int d = 833  ;
#define a1 10
#define a2 11
#define b1 12
#define b2 13

void setup()
{
  pinMode(stepPin, OUTPUT);
  pinMode(a1, INPUT);
  pinMode(a2, INPUT);
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);

  Serial.begin(9600);
  Serial.println("initialized");
}
void loop()
{
  int a1_state = digitalRead(a1);
  int a2_state = digitalRead(a2);
  int b1_state = digitalRead(b1);
  int b2_state = digitalRead(b2);


  if (a1_state == HIGH) {
    Serial.println("a1 high");
  }
  
    if (a2_state == HIGH) {
      Serial.println("a1 high");
    }

    if (b1_state == HIGH) {
      Serial.println("b1 high");
    }

    if (b2_state == HIGH) {
      Serial.println("b2 high");
    }

  
  delayMicroseconds(800);
  Serial.println("--------new Cycle------"); 

  digitalWrite(stepPin, 1);
  delayMicroseconds(800);
  digitalWrite(stepPin, 0);



}
