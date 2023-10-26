#include "lift.h"
#include <usart.h>

void Lift::setup(int interval){
    int ppr = 200;
    bool reversal = false;
    GPIO_TypeDef *pulseGpioX = GPIO?;
    GPIO_TypeDef *dirGpioX = GPIO?;
    uint16_t pulseGpioPin = GPIO_PIN_?;
    uint16_t dirGpioPin = GPIO_PIN_?;
    radius = 10;
    height = 50;
    condition = Condition::Down;
    stepperMotor = StepperMotor();
    stepperMotor.setup(interval, ppr, reversal, pulseGpioX, dirGpioX, pulseGpioPin, dirGpioPin);
}

void Lift::update(int deltaTime){
    stepperMotor.update(deltaTime);
    if (stepperMotor.getHasFinished()){
        if (condition == Condition::Dropping) {
            condition = Condition::Down;
        }
        if (condition == Condition::Lifting){
            condition = Condition::Up;
        }
    }
}

void Lift::lift(){
    if (condition != Condition::Down) return;
    double radian = height / radius;
    stepperMotor.rotateInRadians(radian);
    condition = Condition::Lifting;
}

void Lift::drop(){
    if (condition != Condition::Up) return;
    stepperMotor.setRotation(0);
    condition = Condition::Dropping;
}

bool Lift::getHasFinished(){
    return stepperMotor.getHasFinished();
}