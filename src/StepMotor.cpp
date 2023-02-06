#include "StepMotor.h"

StepMotor::StepMotor(unsigned int pinA, unsigned int pinB, unsigned int pinC, unsigned int pinD, unsigned int stepDelay, bool isSequence8) 
    : _pinA(pinA), _pinB(pinB), _pinC(pinC), _pinD(pinD), _stepDelay(stepDelay), _isSequence8(isSequence8)
{
}

unsigned int StepMotor::_degree2Steps(unsigned int degrees) 
{
  const float motorStepAngle = 5.625;
  int motorStepsPerStepAngle = 32;
  float sequence = 4; 

  if(_isSequence8) {
    motorStepsPerStepAngle = 64;
    sequence = 8; 
  }

  float steps4Degrees = (float) degrees / motorStepAngle;
  return (int)(steps4Degrees *  (float) motorStepsPerStepAngle) / (float) sequence;
}

void StepMotor::_sequence4() 
{
    setAB();
    delay(_stepDelay);
    setBC();
    delay(_stepDelay);
    setCD();
    delay(_stepDelay);
    setDA();
    delay(_stepDelay);
}

void StepMotor::_sequence8() 
{
    setA();
    delay(_stepDelay);
    setAB();
    delay(_stepDelay);
    setB();
    delay(_stepDelay);
    setBC();
    delay(_stepDelay);
    setC();
    delay(_stepDelay);
    setCD();
    delay(_stepDelay);
    setD();
    delay(_stepDelay);
    setDA();
    delay(_stepDelay);
}

void StepMotor::_reset() 
{
    digitalWrite(_pinA, LOW);
    digitalWrite(_pinB, LOW);
    digitalWrite(_pinC, LOW);
    digitalWrite(_pinD, LOW);
}

void StepMotor::setA() 
{
    _reset();
    digitalWrite(_pinA, HIGH);
}

void StepMotor::setB() 
{
    _reset();
    digitalWrite(_pinB, HIGH);
}

void StepMotor::setC() 
{
    _reset();
    digitalWrite(_pinC, HIGH);
}

void StepMotor::setD() 
{
    _reset();
    digitalWrite(_pinD, HIGH);
}

void StepMotor::setAB() 
{
    _reset();
    digitalWrite(_pinA, HIGH);
    digitalWrite(_pinB, HIGH);
}

void StepMotor::setBC() 
{
    _reset();
    digitalWrite(_pinB, HIGH);
    digitalWrite(_pinC, HIGH);
}

void StepMotor::setCD() 
{
    _reset();
    digitalWrite(_pinC, HIGH);
    digitalWrite(_pinD, HIGH);
}

void StepMotor::setDA() 
{
    _reset();
    digitalWrite(_pinD, HIGH);
    digitalWrite(_pinA, HIGH);
}

// 180° Drehung => 180° / 11.25° = 16
// 16 * 32 Schritte = 512
// 11.25° bei 32 Schritten (4 Sequence)
void StepMotor::stepDegree(unsigned int degrees) 
{
    auto steps2End = _degree2Steps(degrees);
    unsigned int countSteps = 0;

    while(countSteps < steps2End) 
    {
        if(_isSequence8)
            _sequence8();
        else
            _sequence4();

        countSteps++;
    }
}