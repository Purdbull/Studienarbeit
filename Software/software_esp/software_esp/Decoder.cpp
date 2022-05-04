#include "Arduino.h"
#include "Decoder.h"
#include "State.h"

Decoder::Decoder() {}

int Decoder::getHeader(byte message) {
  byte headerMask = B00000011;
  byte result = message & headerMask;
  if (result > 0) {
    return result;
  }
  else if (Decoder::getTail(message) == 1) {
    return HEADER_ASK; //header_ask
  } 
  else if (Decoder::getTail(message) == 2) {
    return HEADER_BATTERY;  //header_battery
  }
  return 5;
}



byte Decoder::getBody(byte message) {
  byte bodyMask = B00111100;
  byte result = message & bodyMask;
  return (result >> 2);
}

int Decoder::getTail(byte message) {
  byte tailMask = B11000000;
  byte result = message & tailMask;
  return (int)(result >> 6);
}

int Decoder::getPosition(String message){
  return message.toInt();
}
