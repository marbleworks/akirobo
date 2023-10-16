#ifndef PULSESENDER_H
#define PULSESENDER_H

#include "repeater.h"

class PulseSender {
    private:
        Repeater repeater;
        bool high;
    public:
        void setup();
        void init();
        void start(int interval, int pulses);
        void interrupt();
        void finish();
        void update(int deltaTime);
        void send(bool high);
        void sendToggle();
        int getCurrentPulses();
        bool getIsSending();
        bool getHasFinished();
};

#endif