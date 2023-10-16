#include "holder.h"
#include "stepperMotor.h"

void Holder::setup(int interval){
    int ppr = 200;
    radius = 10;
    openDistance = 300; // fix needed
    x = 207;
    y = 97;
    z = 57;
    condition = Condition::Open; // Firstly, holder is open.
    stepperMotor = StepperMotor();
    stepperMotor.setup(interval, ppr);
}

void Holder::update(int deltaTime){
    stepperMotor.update(deltaTime);
    if (stepperMotor.getHasFinished()){
        if (condition == Condition::Closing) {
            condition = Condition::Close;
        }
        if (condition == Condition::Opening){
            condition = Condition::Open;
        }
    }
}

// holdType: 0 -> x, 1 -> y, 2 -> z
void Holder::hold(int holdType, int num){
    if (condition != Condition::Open) return;
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
    condition = Condition::Closing;
}

void Holder::release(){
    if (condition != Condition::Close) return;
    stepperMotor.setRotation(0);
    condition = Condition::Opening;
}

bool Holder::getHasFinished(){
    return stepperMotor.getHasFinished();
}