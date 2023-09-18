#ifndef HOLDER_H
#define HOLDER_H

#include "stepperMotor.h"

class Holder {
    private:
        StepperMotor stepperMotor;
        int interval;
        int ppr;
        int deltaTime;
        double radius;
        double openDistance;
        double x;
        double y;
        double z;
        bool isClose;
        bool isOpen;
        bool isClosing;
        bool isOpening;
    public:
        Holder();
        void start();
        void update();
        void hold(int holdType, int num);
        void release();
        bool getHasFinished();
};

#endif