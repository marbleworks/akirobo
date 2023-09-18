#include "stepperMotor.h"
#include <math.h>

StepperMotor::StepperMotor(){
    pulseSender = PulseSender();
    interval = 0;
    ppr = 0;
    rotation = 0;
};

void StepperMotor::init(int interval, int ppr){
    this->interval = interval;
    this->ppr = ppr;
}

void StepperMotor::update(int deltaTime){
    pulseSender.update(deltaTime);
    if (pulseSender.getIsSending() || pulseSender.getHasFinished()){
        rotation = tmpRotation + pulseSender.getCurrentPulses();
        if (pulseSender.getHasFinished()){
            onFinishedRotation();
        }
    }
}

void StepperMotor::setRotation(int value){
    int diff = value - rotation;
    rotate(diff);
}

void StepperMotor::setRotationInRadians(double radian){
    setRotation(radianToPulses(radian));
}

void StepperMotor::rotate(int value){
    tmpRotation = rotation;
    setDirection(value >= 0);
    pulseSender.start(interval, value);
}

void StepperMotor::rotateInRadians(double radian) {
    rotate(radianToPulses(radian));
}

void StepperMotor::onFinishedRotation(){
    
}

// fix needed
void StepperMotor::setDirection(bool positive) {
    if (positive){
        HAL_GPIO_WritePin(GPIOQ,GPIO_PIN_1000,GPIO_PIN_SET); // Process needed to open the holder.
    }
    else{
        HAL_GPIO_WritePin(GPIOQ,GPIO_PIN_1000,GPIO_PIN_SET); // Process needed to close the holder.
    }
}

int StepperMotor::radianToPulses(double radian){
    return (int) round((radian * ppr) / (2 * M_PI));
}

bool StepperMotor::getHasFinished(){
    return pulseSender.getHasFinished();
}