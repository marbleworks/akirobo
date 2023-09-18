#include "holder.h"

extern "C"{
    int deltaTime = 1;
    Holder holder = Holder();

    void start(){
        holder.start();
    }

    void update(){
        input();
        holder.update();
    }

    void input(){
        if (controller.B == 1){
            holder.hold(2, 3);
        }
        if (controller.Y == 1){
            holder.release();
        }
    }


    void main_cpp(){
        start();
        while (true){
            update()
            HAL_DELAY(deltaTime);
        }
    }
}