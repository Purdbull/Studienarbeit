#include "Drivehandler.h"
#include "HighTrainStepper.h"
#include "EEPROM.h"

Drivehandler::Drivehandler(int f, int t, Stepper* st) {
  this->from = f;
  this->to = t;
  this->isDrivingForward = this->to > this->from;
  if (this->isDrivingForward) {
    this->driveArrayMaxIndex = this->to - this->from;
  }
  else {
    this->driveArrayMaxIndex = this->from - this->to;
  }

  this->stepper = st;
}

Drivehandler::~Drivehandler() {
}




void Drivehandler::drive() {
  Drivehandler::setDriveSpeeds();
  byte pos = EEPROM.read(0);
  if (this->isDrivingForward) {
    for (int i = 0; i < this->driveArrayMaxIndex; i++) {
      //detach intterrupt
      //jans funkton mit parameter von driveSpeeds[i] solang kein reed kam
      //wichtig::zeitwatchdog für fehler
      //position aktualisieren in eeprom
      //Serial.print("Moritz will zu ");
      //Serial.println(driveSpeeds[i]);
      this->stepper->linear(driveSpeeds[i]);
      delay(7000); //fake reed contact
      if (pos < 8) {
        pos++;
      }
    }
  }
  else {
    int s = 0;
    for (int i = 0; i < this->driveArrayMaxIndex; i++) {
      //detach intterrupt
      //jans funkton mit parameter von driveSpeeds[i]*-1 solang kein reed kam
      //wichtig::zeitwatchdog für fehler
      //position aktualisieren in eeprom
      s = driveSpeeds[i] * (-1);
      //Serial.print("Moritz will zu ");
      //Serial.println(s);
      this->stepper->linear(s);
      delay(7000); //fake reed contact
      if (pos > 0) {
        pos--;
      }
    }
  }
  EEPROM.write(0, pos);
  if (this->to == 0 || this->to == 7) {
    this->stepper->stopMode(2);//3 with reed attached
  }
  else {
    this->stepper->stopMode(2);
  }
  //irgendwie interrupt melden zum neustart oder erfolg melden
}




void Drivehandler::setDriveSpeeds() {

  for (int i = 0; i <= this->driveArrayMaxIndex; i++) {
    if (isDrivingForward) {
      this->driveSpeeds[i] = this->sectionSpeeds[(this->from + i)];
    } else {
      this->driveSpeeds[i] = this->sectionSpeeds[(this->from - i)];
    }
  }

  //prio3
  if (this->driveSpeeds[0] > this->driveSpeeds[1]) {
    this->driveSpeeds[0] = this->driveSpeeds[1];
  }

  //prio2
  if (this->driveSpeeds[(this->driveArrayMaxIndex - 1)] > 50) {
    this->driveSpeeds[(this->driveArrayMaxIndex - 1)] = 50;
  }

  //prio1
  driveSpeeds[this->driveArrayMaxIndex] = 0;
  //Serial.print("Drive Array: ");
  //for (int i = 0; i <= this->driveArrayMaxIndex; i++) {
  //Serial.print(driveSpeeds[i]);
  //Serial.print(", ");
  //}
  //Serial.println();
}
