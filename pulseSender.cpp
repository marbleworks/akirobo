#include "pulseSender.h"
#include <cmath>
// additional include needed

void PulseSender::setup(){
    repeater = Repeater();
}

void PulseSender::init(){
    high = false;
}

void PulseSender::start(int interval, int pulses){
    init();
    sendToggle();
    repeater.start(interval, pulses * 2 - 1);
}

void PulseSender::interrupt(){
    init();
    repeater.interrupt();
    send(false);
}

void PulseSender::finish(){
    init();
}

void PulseSender::update(int deltaTime){
    repeater.update(deltaTime);
    if (repeater.getFlag()) sendToggle();
    if (repeater.getHasFinished()) finish();
}

void PulseSender::sendToggle(){
    high = !high;
    send(high);
}

void PulseSender::send(bool high){
    if (high){
        HAL_GPIO_WritePin(GPIOW,GPIO_PIN_1000,GPIO_PIN_SET); // fix needed
    }
    else{
        HAL_GPIO_WritePin(GPIOW,GPIO_PIN_1000,GPIO_PIN_RESET); // fix needed
    }
}

int PulseSender::getCurrentPulses(){
    return std::floor((double) repeater.getRepeatCount() / (double) 2) + 1;
}

bool PulseSender::getIsSending(){
    return repeater.getIsRepeating();
}

bool PulseSender::getHasFinished(){
    return repeater.getHasFinished();
}