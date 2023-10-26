#ifndef LIFT_H
#define LIFT_H

#include "stepperMotor.h"

class Lift {
    private:
        StepperMotor stepperMotor;
        double radius;
        double height;
        enum class Condition {Down, Up, Dropping, Lifting};
        Condition condition;
    public:
        void setup(int interval);
        void update(int deltaTime);
        void lift();
        void drop();
        bool getHasFinished();
};

#endif