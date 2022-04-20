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

    int targetIr; //target speed

    //int k; //counter for ISR Prescaler,
    //int a; //accelecaration (modulo)
    //bool yDone; ;
    //int s;


    void stepMode(int);
    void en();
    void dis();
    void setDir(int);


  public:

    Stepper();
    ~Stepper();
    void initInterrupts();

    void linear();
    void mode(int n);
    void isr();



};

#endif
