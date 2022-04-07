#include <HCSR04.h>
#define led1 9
#define led2 12
#define warn 20
#define safe 10


byte triggerPin = 6;
byte echoCount = 2;
byte* echoPins = new byte[echoCount] { 7, 11 };

void setup () {
  Serial.begin(9600);
  HCSR04.begin(triggerPin, echoPins, echoCount);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

}

void loop () {
  double* distances = HCSR04.measureDistanceCm();
  /*
  for (int i = 0; i < echoCount; i++) {
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(distances[i]);
    Serial.println(" cm");
  }
*/
  Serial.print("Sensor1: ");
  Serial.println(String(checkDist(distances[0])));
  Serial.print("Sensor2: "); 
  Serial.println(String(checkDist(distances[1]))); 

  
  delay(250);
}

byte checkDist(double distance) {
  byte field = 0; 
  if (distance < warn){
    field = 1; 
  }

  if (distance < safe){
    field = 2; 
  }

  return field; 

}
