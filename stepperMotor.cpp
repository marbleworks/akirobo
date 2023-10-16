#include "stepperMotor.h"
#include <cmath>
#include <numbers>
// additional include needed

void StepperMotor::setup(int interval, int ppr){
    pulseSender = PulseSender();
    pulseSender.setup();
    this->interval = interval;
    this->ppr = ppr;
}

void StepperMotor::init(){
    rotation = 0;
    tmpRotation = 0;
    tmpDirection = false;
}

void StepperMotor::update(int deltaTime){
    pulseSender.update(deltaTime);
    if (pulseSender.getIsSending() || pulseSender.getHasFinished()){
        int multiplier = tmpDirection ? 1 : -1;
        rotation = tmpRotation + pulseSender.getCurrentPulses() * multiplier;
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
    tmpDirection = value >= 0;
    setDirection(tmpDirection);
    pulseSender.start(interval, std::abs(value));
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
    return (int) std::round((radian * ppr) / (2 * std::numbers::pi));
}

bool StepperMotor::getHasFinished(){
    return pulseSender.getHasFinished();
}