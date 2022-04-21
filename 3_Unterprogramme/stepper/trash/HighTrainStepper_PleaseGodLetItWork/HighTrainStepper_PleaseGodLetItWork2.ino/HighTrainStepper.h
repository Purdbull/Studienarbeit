#include <Arduino.h>
#ifndef HighTrainStepper_h
#define HighTrainStepper_h


// PinOut
#define DIR 7
#define CLK 8
#define ENBL 5
#define M0 10
#define M1 9
#define LED 9



class Stepper {
  private:

    int targetRegVal; //target speed

    int count; //counter for ISR Prescaler,
    int acc; //accelecaration (modulo)
    bool accDone; ;
    int s;


    void setDir(int targetSpeed);


  public:
    void dis();

    Stepper();
    ~Stepper();
    void initInterrupts();
    void en();

    void linear(int targetVal, int targetAcc = 50);
    void mode(int n);
    void isr();
    void stepMode(int mode);



};

#endif
