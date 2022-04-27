#include "Drivehandler.h"

Drivehandler::Drivehandler(int f, int t, Stepper* step) {
  this->from = f;
  this->to = t;
  this->isDrivingForward = this->to > this->from;
  if(this->isDrivingForward){    
    this->driveArrayMaxIndex = this->to - this->from;
  }
  else{
    this->driveArrayMaxIndex = this->from - this->to;
  }

  this->stepper = step;

  stepper->initInterrupts();
}

Drivehandler::~Drivehandler() {
}




void Drivehandler::drive(){
  Drivehandler::setDriveSpeeds();
  if(this->isDrivingForward){
    for(int i = 0; i < this->driveArrayMaxIndex; i++){
      //detach intterrupt
      //jans funkton mit parameter von driveSpeeds[i] solang kein reed kam
      //wichtig::zeitwatchdog für fehler
      //position aktualisieren in eeprom
      stepper->linear(driveSpeeds[i]);
      delay(6000);
    }
  }
  else{
    for(int i = 0; i < this->driveArrayMaxIndex; i++){
      //detach intterrupt
      //jans funkton mit parameter von driveSpeeds[i]*-1 solang kein reed kam
      //wichtig::zeitwatchdog für fehler
      //position aktualisieren in eeprom
      stepper->linear(driveSpeeds[i]);
      delay(6000);
    }
  }

  if(this->to == 0 || this->to == 7){
    //jan endfahrt
  }
  else{
    //jan mit 0
  }


  //irgendwie interrupt melden zum neustart oder erfolg melden
}




void Drivehandler::setDriveSpeeds() {
  if(isDrivingForward){
    //prio 4
    for (int i = 0; i <= this->driveArrayMaxIndex; i++) {
      this->driveSpeeds[i] = this->sectionSpeeds[(this->from + i)]; 
    }
  }
  
  else{ 
    //prio 4
    for (int i = 0; i <= this->driveArrayMaxIndex; i++) {
      this->driveSpeeds[i] = this->sectionSpeeds[(this->to - i)]; 
    }
  }
  
  //prio3
  if (this->driveSpeeds[0] > this->driveSpeeds[1]) {
    this->driveSpeeds[0] = this->driveSpeeds[1];
  }

  //prio2
  if(this->driveSpeeds[(this->driveArrayMaxIndex-1)] > 50){
    this->driveSpeeds[(this->driveArrayMaxIndex-1)] = 50;
  }

  //prio1
  driveSpeeds[this->driveArrayMaxIndex] = 0; 
}
