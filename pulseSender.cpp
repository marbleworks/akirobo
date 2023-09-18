#include "pulseSender.h"
#include <math.h>

PulseSender::PulseSender(){
    repeater = Repeater();
    high = false;
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
        HAL_GPIO_WritePin(GPIOW,GPIO_PIN_1000,GPIO_PIN_SET);
    }
    else{
        HAL_GPIO_WritePin(GPIOW,GPIO_PIN_1000,GPIO_PIN_RESET);
    }
}

int PulseSender::getCurrentPulses(){
    return floor((double) repeater.getRepeatCount() / (double) 2) + 1;
}

bool PulseSender::getIsSending(){
    return repeater.getIsRepeating();
}

bool PulseSender::getHasFinished(){
    return repeater.getHasFinished();
}