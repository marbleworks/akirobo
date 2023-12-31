#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include "pulseSender.h"

class StepperMotor {
    private:
        PulseSender pulseSender;
        int interval;
        int ppr;
        bool reversal;
        GPIO_TypeDef *dirGpioX;
        uint16_t dirGpioPin;
        int rotation;
        int tmpRotation;
        bool tmpDirection;
    public:
        void setup(int interval, int ppr, bool reversal, GPIO_TypeDef *pulseGpioX, GPIO_TypeDef *dirGpioX, uint16_t pulseGpioPin, uint16_t dirGpioPin);
        void init();
        void update(int deltaTime);
        void setRotation(int value); // (ex) ppr = 200 -> 1 = 360/200 deg
        void setRotationInRadians(double radian);
        void rotate(int value);
        void rotateInRadians(double radian);
        void onFinishedRotation();
        void setDirection(bool positive);
        int radianToPulses(double radian);
        bool getHasFinished();
};

#endif