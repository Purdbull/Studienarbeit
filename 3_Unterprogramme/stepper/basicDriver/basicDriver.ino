void setup() {
  pinMode(1,OUTPUT); 
  pinMode(3,OUTPUT); 

  digitalWrite(3,1); 

}

void loop() {


  digitalWrite(1,0); 
  delayMicroseconds(800); 
  digitalWrite(1,1); 
  delayMicroseconds(800); 
  

}
