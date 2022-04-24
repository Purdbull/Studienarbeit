/*HighTrainStepper Script
   Bantle & Knapp Copyright
   V3 - March 2022

   Changes:
   stopModes implemented
*/
#include <HCSR04.h>
#include "HighTrainStepper.h"

Stepper* stepper = new Stepper();



//-------------setup---------------
void setup() {
  Serial.begin(9600);
  stepper ->  initInterrupts();


}


//-----------------ISR-----------------

ISR(TIMER1_COMPA_vect) { //Timer1 Interrupt Service Routine
  stepper -> isr();

}

//-------------main--------------
void loop() {



  //Dianas rasante Fahrt mit der Achterbahn-Seilbahn
  Serial.println("Diana auf der Überholspur");
  stepper -> linear(70, 25); //Diana auf der Überholspur
  delay(17000);
  Serial.println("noch schniiiieeeeeeelllleR!");

  stepper -> linear(98, 50); //noch schniiiieeeeeeelllleR!
  delay(15000);
  Serial.println("Moment, wir nehmen die Ganzz Gustav noch mit!!");

  stepper -> stopMode(1); //"Moment, wir nehmen die Ganzz Gustav noch mit!!
  delay(4000);
  Serial.println("Achtung, zurück --> Ich komme! tutTuuuuut!");

  stepper -> linear(-20, 100); //Achtung, zurück --> Ich komme! tutTuuuuut!
  delay(7000);
  Serial.println("Ich zeig dir mal, wie gut ich Rückwärts fahren kann!");

  stepper -> linear(-80, 60); //Ich zeig dir mal, wie gut ich Rückwärts fahren kann!
  delay(9000);

  Serial.println("Kukuk, ich halte grad an!");

  stepper -> stopMode(2); //Kukuk, ich halte grad an!
  delay(8000);
  Serial.println("Die Achterbahn Fahrt geht los!");

  stepper -> linear(100, 100); // Die Achterbahn Fahrt geht los!
  delay(7000);
  Serial.println("Umkehrschub!");

  stepper ->stopMode(1); //Umkehrschub!
  delay(6000);
  Serial.println("Die Achterbahn Fahrt geht los!");

  stepper -> linear(-100, 100); // Die Achterbahn Fahrt geht los!
  delay(7000);
  Serial.println("Der große Rausschmeißer!");

  stepper -> linear(100, 100); //Der große Rausschmeißer!
  delay(8000);
  Serial.println("und jetzt gemütlich!");

  stepper -> linear(20, 30); //und jetzt gemütlich!
  delay(10000);
  Serial.println("und jetzt gemütlich!");

  stepper -> linear(0, 30); //und jetzt gemütlich!
  delay(4000);
  Serial.println("//Endstation!");

  stepper -> stopMode(2); //Endstation!
}


/*

  //stopBackwards
  delay(7000);
  stepper -> linear(40);
  delay(7000);
  stepper -> stopMode(1);
  delay(7000);
  stepper -> linear(-50, 100);
  delay(7000);
  stepper -> stopMode(2);
  delay(8000);
  stepper -> linear(80,100);
  delay(7000);
  stepper ->stopMode(3);
  delay(6000);
  stepper ->stopMode(4);
  delay(3000);
*/

/*

  //normalDrive
  delay(7000);
  stepper -> linear(100);
  delay(7000);
  stepper -> linear(20, 100);
  delay(7000);
  stepper -> linear(40);
  delay(7000);
  stepper -> linear(0);
*/

/*
  //bothDirections
  delay(7000);
  stepper -> linear(100);
  delay(7000);
  stepper -> linear(-20, 100);
  delay(7000);
  stepper -> linear(0);
  delay(7000);
  stepper -> linear(-60);
*/
