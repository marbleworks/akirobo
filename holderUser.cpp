#include "holder.h"
// additional include needed

extern "C"{
    int deltaTime = 1;
    int interval = 1;
    Holder holder;

    void start(){
        holder = Holder();
        holder.setup(interval);
    }

    void input(){
        if (controller.B == 1){
            holder.hold(2, 3);
        }
        if (controller.Y == 1){
            holder.release();
        }
    }

    void update(){
        input();
        holder.update(deltaTime);
    }

    void main_cpp(){
        start();
        while (true){
            update()
            HAL_Delay(deltaTime);
        }
    }
}