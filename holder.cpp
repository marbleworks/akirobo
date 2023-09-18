#include "holder.h"
#include "stepperMotor.h"

Holder::Holder(){
    stepperMotor = StepperMotor();
    interval = 1;
    ppr = 200;
    deltaTime = 1;
    radius = 50; // fix needed
    openDistance = 300; // fix needed
    x = 207;
    y = 97;
    z = 57;
    isClose = false;
    isOpen = true; // Firstly, holder is open.
    isClosing = false;
    isOpening = false;
}

void Holder::start(){
    stepperMotor.init(interval, ppr);
}

void Holder::update(){
    stepperMotor.update(deltaTime);
    if (stepperMotor.getHasFinished()){
        if (isClosing) {
            isClose = true;
            isClosing = false;
        }
        if (isOpening){
            isOpen = true;
            isOpening = false;
        }
    }
}

// holdType: 0 -> x, 1 -> y, 2 -> z
void Holder::hold(int holdType, int num){
    if (!isOpen) return;
    double distance = 0;
    if (holdType == 0) {
        distance = x * num;
    }
    if (holdType == 1) {
        distance = y * num;
    }
    if (holdType == 2) {
        distance = z * num;
    }
    double diff = (openDistance - distance) / 2;
    double radian = diff / radius;
    stepperMotor.rotateInRadians(-radian);
    isOpen = false;
    isClosing = true;
}

void Holder::release(){
    if (!isClose) return;
    stepperMotor.setRotation(0);
    isClose = false;
    isOpening = true;
}

bool Holder::getHasFinished(){
    return stepperMotor.getHasFinished();
}