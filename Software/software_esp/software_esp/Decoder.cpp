#include "Arduino.h"
#include "Decoder.h"

Decoder::Decoder() {}

int Decoder::getHeader(byte message) {
  byte headerMask = B00000011;
  byte result = message & headerMask;
  if (result > 0) {
    return result;
  }
  else if (Decoder::getTail(message) == 1) {
    return 4; //header_ask
  } 
  else if (Decoder::getTail(message) == 2) {
    return 0;  //header_battery
  }
  return 5;
}



int Decoder::getBody(byte message) {
  byte bodyMask = B00111100;
  byte result = message & bodyMask;
  return (int)(result >> 2);
}

int Decoder::getTail(byte message) {
  byte tailMask = B11000000;
  byte result = message & tailMask;
  return (int)(result >> 6);
}

int Decoder::getPosition(String message){
  return message.toInt();
}
