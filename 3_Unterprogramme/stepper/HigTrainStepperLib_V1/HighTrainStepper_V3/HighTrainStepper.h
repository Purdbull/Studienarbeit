#include <Arduino.h>
class Stepper {
  private:
    // Min and Max values for timer compare Register OCR1A
#define Max  5500
#define Min 990

    //Min and Max Values for acceleration (additional prescaler with modulo)
#define aMax 20
#define aMin 4

    int y; //target speed
    int k; //counter for ISR Prescaler,
    int a; //accelecaration (modulo)
    bool yDone; ;
    int s;


    initInterrupts();


  public:

    Stepper(int clk, int dir, int en, int m0, int m1) {
      this -> clk = clk;
      this -> dir = dir;
      this -> en = en;
      this -> m0 = m0;
      this -> m1 = m1;

      pinMode(clk, OUTPUT);
      pinMode(dir, OUTPUT);
      pinMode(enbl, OUTPUT);
      pinMode(m0, OUTPUT);
      pinMode(m1, OUTPUT);
      pinMode(led, OUTPUT);
      y = Min;
      yDone = false;
    }

    void linear(int s, int b = 40);

};
