#include "Arduino.h"
#include "IdleState.h"

IdleState::IdleState(){}


int IdleState::handle(String serverMsg){
    //Zustandswechsel?
    return 1;
}

int IdleState::handle(byte arduinoMsg){
    //wenn header stimmt, akku an server schicken

    //wieder in Idlemodus
    return 1;
}
