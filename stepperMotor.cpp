#include "stepperMotor.h"
#include <usart.h>
#include <cmath>
#include <numbers>

void StepperMotor::setup(int interval, int ppr, bool reversal, GPIO_TypeDef *pulseGpioX, GPIO_TypeDef *dirGpioX, uint16_t pulseGpioPin, uint16_t dirGpioPin){
    pulseSender = PulseSender();
    pulseSender.setup(pulseGpioX, pulseGpioPin);
    this->interval = interval;
    this->ppr = ppr;
    this->reversal = reversal;
    this->dirGpioX = dirGpioX;
    this->dirGpioPin = dirGpioPin;
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

void StepperMotor::setDirection(bool positive) {
    if (positive ^ reversal){
        HAL_GPIO_WritePin(dirGpioX, dirGpioPin, GPIO_PIN_SET);
    }
    else{
        HAL_GPIO_WritePin(dirGpioX, dirGpioPin, GPIO_PIN_RESET);
    }
}

int StepperMotor::radianToPulses(double radian){
    return (int) std::round((radian * ppr) / (2 * std::numbers::pi));
}

bool StepperMotor::getHasFinished(){
    return pulseSender.getHasFinished();
}