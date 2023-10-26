#include "holder.h"
#include "lift.h"

extern "C"{
    int deltaTime = 1;
    Holder holder;
    int holderInterval = 1;
    Lift lift;
    int liftInterval = 1;


    void start(){
        holder = Holder();
        holder.setup(holderInterval);
        lift = Lift();
        lift.setup(liftInterval);
    }

    //   Y
    // X   B
    //   A
    void input(){
        if (controller.X == 1){
            holder.hold(2, 3);
        }
        if (controller.B == 1){
            holder.release();
        }
        if (controller.Y == 1){
            lift.lift();
        }
        if (controller.A == 1){
            lift.drop();
        }
    }

    void update(){
        input();
        holder.update(deltaTime);
        lift.update(deltaTime);
    }

    void main_cpp(){
        start();
        while (true){
            update()
            HAL_Delay(deltaTime);
        }
    }
}