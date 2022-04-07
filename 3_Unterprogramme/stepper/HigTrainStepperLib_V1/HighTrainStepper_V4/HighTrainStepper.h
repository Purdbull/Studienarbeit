#include <Arduino.h>
#ifndef HighTrainStepper_h
#define HighTrainStepper_h


#define DIR 3
#define CLK 2
#define ENBL 10
#define M0 4
#define M1 5
#define LED 9

// Min and Max values for timer compare Register OCR1A
#define MAX  5500
#define MIN 990

//Min and Max Values for acceleration (additional prescaler with modulo)
#define A_MAX 20
#define A_MIN 4


class Stepper {
  private:

    int y; //target speed

    int k; //counter for ISR Prescaler,
    int a; //accelecaration (modulo)
    bool yDone; ;
    int s;

    void initInterrupts();
    void stepMode(int);
    void en();
    void dis();
    void setDir(int);


  public:

    Stepper();
    ~Stepper();

    void linear(int, int);
    void mode(int n);
    void isr();



};

#endif
