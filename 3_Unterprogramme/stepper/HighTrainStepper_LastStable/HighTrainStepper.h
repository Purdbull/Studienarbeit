#include <Arduino.h>
#ifndef HighTrainStepper_h
#define HighTrainStepper_h


// PinOut
#define DIR 3
#define CLK 2
#define ENBL 10
#define M0 4
#define M1 5
#define LED 9



class Stepper {
  private:

    int targetRegVal; //target speed

    int count; //counter for ISR Prescaler,
    int acc; //accelecaration (modulo)
    bool valDone; ;
    int s;


    void dis();
    void setDir(int targetSpeed);


  public:

    Stepper();
    ~Stepper();
    void initInterrupts();
    void en();

    void linear(int targetVal, int targetAcc);
    void mode(int n);
    void isr();
    void stepMode(int mode);



};

#endif
