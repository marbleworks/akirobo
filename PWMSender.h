#ifndef PWMSENDER_H
#define PWMSENDER_H

class PWMSender {
    private:
        int timer;
        int interval;
    public:
        PWMSender();
        void start(int interval);
        void update(int deltaTime);
};

#endif