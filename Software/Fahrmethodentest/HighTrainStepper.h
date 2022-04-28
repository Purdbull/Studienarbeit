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

    //Vars
    int targetRegVal; //target speed
    int count; //counter for ISR Prescaler,
    int acc; //accelecaration (modulo)
    bool accDone; ;
    int s;

    //Functions
    void en();
    void dis();
    void setDir(int targetSpeed);
    void stepMode(int mode);


  public:
    Stepper();
    ~Stepper();
    void initInterrupts();
    void linear(int targetVal, int targetAcc = 80);
    void stopMode(int n);
    void isr();



};

#endif
