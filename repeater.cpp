#include "repeater.h"

void Repeater::init(){
    timer = 0;
    interval = 0;
    repeatCount = 0;
    currentRepeatCount = 0;
    isRepeating = false;
    flag = false;
    hasFinished = false;
}

void Repeater::start(int interval, int repeatCount){
    init();
    this->interval = interval;
    this->repeatCount = repeatCount;
    isRepeating = true;
}

void Repeater::interrupt(){
    init();
}

void Repeater::finish(){
    isRepeating = false;
    hasFinished = true;
}

void Repeater::update(int deltaTime){
    flag = false;
    hasFinished = false;
    if (!isRepeating) return;
    timer += deltaTime;
    if (timer >= interval){
        timer = 0;
        currentRepeatCount++;
        flag = true;
        if (currentRepeatCount >= repeatCount){
            finish();
        }
    }
}

int Repeater::getRepeatCount(){
    return repeatCount;
}

bool Repeater::getIsRepeating(){
    return isRepeating;
}

bool Repeater::getFlag(){
    return flag;
}

bool Repeater::getHasFinished(){
    return hasFinished;
}