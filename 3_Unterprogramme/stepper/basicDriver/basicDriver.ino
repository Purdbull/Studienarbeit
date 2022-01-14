void setup() {
  pinMode(1,OUTPUT); 
  pinMode(3,OUTPUT); 

  digitalWrite(3,1); 

}

void loop() {


  digitalWrite(1,0); 
  delayMicroseconds(90); 
  digitalWrite(1,1); 
  delayMicroseconds(90); 
  

}
