#include <Arduino.h>
#ifndef HighTrainStepper_h
#define HighTrainStepper_h


// PinOut
#define dir 3
#define clk 2
#define enbl 10
#define m0 4
#define m1 5
#define led 9



class Stepper {
  private:

    int targetRegVal; //target speed

    int count; //counter for ISR Prescaler,
    int acc; //accelecaration (modulo)
    bool valDone; ;
    int s;


    void stepMode(int);
    void dis();
    void setDir(int);


  public:

    Stepper();
    ~Stepper();
    void initInterrupts();
    void en();

    void linear(int targetVal, int targetAcc);
    void mode(int n);
    void isr();



};

#endif
