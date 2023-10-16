#ifndef REPEATER_H
#define REPEATER_H

class Repeater {
    private:
        int timer;
        int interval;
        int repeatCount;
        int currentRepeatCount;
        bool isRepeating;
        bool flag;
        bool hasFinished;
    public:
        void init();
        void start(int interval, int pulses);
        void interrupt();
        void finish();
        void update(int deltaTime);
        int getRepeatCount();
        bool getIsRepeating();
        bool getFlag();
        bool getHasFinished();
};

#endif