#include "Microcontroller.h"

#ifndef STEPMOTOR_H
#define STEPMOTOR_H

class StepMotor
{
private:
    unsigned int _pinA;
    unsigned int _pinB;
    unsigned int _pinC;
    unsigned int _pinD;
    bool _isSequence8;
    unsigned int _stepDelay;
    unsigned int _degree2Steps(unsigned int degrees);
    void _sequence4();
    void _sequence8();
    void _reset();
    
public:
    StepMotor(unsigned int pinA, unsigned int pinB, unsigned int pinC, unsigned int pinD, unsigned int stepDelay = 10, bool isSequence8 = false);
    void setA();
    void setB();
    void setC();
    void setD();
    void setAB();
    void setBC();
    void setCD();
    void setDA();
    void stepDegree(unsigned int degrees);
};

#endif