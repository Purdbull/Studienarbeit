// Define pin connections & motor's steps per revolution
//const int dirPin = 2;
const int stepPin = 1;
const int stepsPerRevolution = 200;
int d = 833;

void setup()
{
  pinMode(stepPin, OUTPUT);

  Serial.begin(9600);
  Serial.println("initialized");
}
void loop()
{
    Serial.println("--------new Cycle------"); 

  digitalWrite(stepPin, 1);
  delayMicroseconds(d);
  digitalWrite(stepPin, 0);
  delayMicroseconds(d);



}
