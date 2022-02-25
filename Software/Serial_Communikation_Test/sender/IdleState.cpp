#include "Arduino.h"
#include "IdleState.h"

IdleState::IdleState(): State(){}

void IdleState::handle(String serverMsg){
    //Zustandswechsel?
}

void IdleState::handle(byte arduinoMsg){
    //wenn header stimmt, akku an server schicken
}
