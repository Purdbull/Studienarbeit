#define LED 2
//globe Variable zum speichern von Daten welche empfangen werden
int data = 0; 

void setup() {
  //Begin der Seriellen Kommunikation mit 9600 baud
  Serial.begin(9600);
  
}
void loop() {
  //Wenn Daten zur Verfügung stehen dann...
  if (Serial.available() > 0) {
    //lesen von Daten
    if(Serial.read() == (byte)2){
      Serial.write(0);
    }
    //Die Daten werden in ASCII Zeichen (0..255) gesendet und empfangen,
    //um diese Zeichen lesen zu können müssen diese Werte in Zeichen (Char) umgewandelt werden
    delay(5000);
  }
}
