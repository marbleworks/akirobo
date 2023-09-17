#include "pwmSender.h"

PWMSender::PWMSender(){
    timer = 0;
    interval = 0;
}

void PWMSender::start(int interval){
    this->interval = interval;
}

void PWMSender::update(int deltaTime){
    timer += deltaTime;
    if (timer >= interval){
        timer -= interval;

        
    }
}