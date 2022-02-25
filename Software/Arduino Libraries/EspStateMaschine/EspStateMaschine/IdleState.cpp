#include "Arduino.h"
#include "IdleState.h"

IdleState::IdleState() : State(){}

IdleState::handle(String serverMsg){
    //Zustandswechsel?
}

IdleSTate::handle(byte arduinoMsg){
    //wenn header stimmt, akku an server schicken
}