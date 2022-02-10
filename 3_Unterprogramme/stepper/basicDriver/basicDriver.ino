void setup() {
  pinMode(2,OUTPUT); 
  pinMode(3,OUTPUT); 

  digitalWrite(3,0); 

}

void loop() {


  digitalWrite(2,0); 
  delayMicroseconds(200); 
  digitalWrite(2,1); 
  delayMicroseconds(200); 
  

}
