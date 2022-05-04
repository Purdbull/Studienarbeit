#include "Arduino.h"

#ifndef Decoder_h
#define Decoder_h

class Decoder{
    public:
        Decoder();
        int getHeader(byte);
        byte getBody(byte);
        int getTail(byte);
        int getPosition(String);
};

#endif
