#ifndef HOLDER_H
#define HOLDER_H

#include "stepperMotor.h"

class Holder {
    private:
        StepperMotor stepperMotor;
        double radius;
        double openDistance;
        double x;
        double y;
        double z;
        enum class Condition {Close, Open, Closing, Opening};
        Condition condition;
    public:
        void setup(int interval);
        void update(int deltaTime);
        void hold(int holdType, int num);
        void release();
        bool getHasFinished();
};

#endif