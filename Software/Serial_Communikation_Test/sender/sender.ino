#define LED 2

void setup() {
  //Begin der Seriellen Kommunikation mit 9600 baud 
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  //senden von "Hallo Welt!" über die Serielle Schnittstelle
  
}
void loop() {
  Serial.write(2);
  delay(500);
  if(Serial.available() > 0){
    if(Serial.read() == (byte)0){
      digitalWrite(LED, HIGH);
      delay(1000);
      digitalWrite(LED, LOW);
    }
  }
}
