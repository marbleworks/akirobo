#include <main.h>

//extern"C"{
//	void main_cpp(){
//		while (true) {
//			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
//			HAL_Delay(1000);
//			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
//			HAL_Delay(1000);
//		}e
//	}
// }

#include <main.h>
#include <usart.h>
//タイマーを使うときはtim.hを有効化
#include <tim.h>
#include "stm32f1xx_hal_uart.h"		// SBDBTとUART通信をするためのライブラリ
#include "UART1_F710.hpp"
#include<cmath>
#include<numbers>

//使う関数


//auto& get_htim(int index)
//{
//    switch(index)
//    {
//        case 1:
//        return htim1;
//        case 2:
//        return htim2;
//        case 3:
//        return htim3;
//    }
//}

auto get_channel(int index)
{
    switch(index)
    {
        case 1:
        return TIM_CHANNEL_1;
        case 2:
        return TIM_CHANNEL_2;
        case 3:
        return TIM_CHANNEL_3;
    }
}

auto& get_gpio(int index)
{
switch(index)
    {
        case 1:
        return GPIOA;
        case 2:
        return GPIOA;
        case 3:
        return GPIOA;
    }
}

auto& get_gpio_pin(int index)
{
switch(index)
    {
        case 1:
        return GPIO_PIN_11;
        case 2:
        return GPIO_PIN_10;
        case 3:
        return GPIO_PIN_9;
    }
}

void moter_power(bool is_negative, double v_abs, int index)
{
   // auto& htim = get_htim(index);
    auto channel = get_channel(index);
    auto& gpio = get_gpio(index);
    auto& gpio_pin = get_gpio_pin(index);

    __HAL_TIM_SET_COMPARE(&htim2, channel, v_abs);
    if(is_negative){
       HAL_GPIO_WritePin(gpio,gpio_pin,GPIO_PIN_SET);

    }
    else {
       HAL_GPIO_WritePin(gpio,gpio_pin,GPIO_PIN_RESET);
     }
}

void moters_power(double v,double θ){
    double t1 = v*cos(θ);
    double t2 = v*cos(θ-std::numbers::pi/3);
    double t3 = v*cos(θ+std::numbers::pi/3);

    moter_power(std::signbit(t1), std::abs(t1), 1);
    moter_power(std::signbit(t2), std::abs(t2), 2);
    moter_power(std::signbit(t3), std::abs(t3), 3);
}

void polar_coordinates(int x, int y)
{
    int X = x - 64;
    int Y = y - 64;
    double v = 35999*std::sqrt(X*X + Y*Y)/std::sqrt(8192);
    if(X>0)
    {
        double θ = std::atan(Y/X);
    }
    if(X<0)
    {
        double θ = -std::atan(Y/X);
    }
    if(X=0 && Y>0)
    {
        double θ = std::numbers::pi/2;
    }
    if(X=0 && Y<0)
    {
        double θ = -std::numbers::pi/2;
    }

}


// メイン関数
extern "C" {
    void main_cpp()
    {
	// UART開始
	// HAL_UART_RxCpltCallbackでRecevie_ITしている
	HAL_UART_Receive_IT(&huart2, controller.RxBuffer, 8);

	//LEDについて緑は常に点灯。enableのとき黄色が点灯。disableのとき赤色が点灯するようにする。
    //	 LED緑を点灯
	HAL_GPIO_WritePin(GPIOC, GREEN_LED_Pin, GPIO_PIN_SET);
    //	 黄色LEDを消灯、赤色LEDを点灯
	HAL_GPIO_WritePin(GPIOC, YELLOW_LED_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, RED_LED_Pin, GPIO_PIN_SET);

	int k = 0;
	//k=0で閉じている
	//k=1で移動中
	//k=2で開いている

	// メインループ
	while(true)
	{
		// もし、BACKボタンが押されている(Back == 1)なら、(disable)
		if(controller.Back == 1)
		{
			//LED適宜有効化する
//			 無効化後、黄色LEDを消灯、赤色LEDを点灯
			HAL_GPIO_WritePin(GPIOC, YELLOW_LED_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOC, RED_LED_Pin, GPIO_PIN_SET);
//
//			 LED緑を点灯
			HAL_GPIO_WritePin(GPIOC, GREEN_LED_Pin, GPIO_PIN_SET);

			//PWM無効化　HAL_TIM_PWM_Stop()をかく
			HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
			HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
			HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
		}

		// もし、STARTボタンが押されている(Start == 1)なら、(enable)
		if(controller.Start == 1)
		{
			//LED適宜有効化する
            //			 有効化後、黄色LEDを点灯、赤色LEDを消灯
			HAL_GPIO_WritePin(GPIOC, YELLOW_LED_Pin, GPIO_PIN_SET);
	    	HAL_GPIO_WritePin(GPIOC, RED_LED_Pin, GPIO_PIN_RESET);
            //
            //			 LED緑を点灯
     		HAL_GPIO_WritePin(GPIOC, GREEN_LED_Pin, GPIO_PIN_SET);

			//PWM有効化 HAL_TIM_PWM_Start
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);

		}

		if(controller.B == 1 && k = 0){
			//把持機構
			//モーター回す
            int i = 0;
            HAL_GPIO_WritePin(GPIOQ,GPIO_PIN_1000,GPIO_PIN_SET);
            //Q1000pinをENAにつなげる
            HAL_GPIO_WritePin(GPIOP,GPIO_PIN_1000,GPIO_PIN_SET);
            //P1000ピンをDIRにつなげる
            k = 1;
		}
		if(controller.Y == 1 && k = 2){
			//把持機構
			//モーター回す
		    int j = 0;
		    HAL_GPIO_WritePin(GPIOQ,GPIO_PIN_1000,GPIO_PIN_SET);
		    //Q1000pinをENAにつなげる
		    HAL_GPIO_WritePin(GPIOP,GPIO_PIN_1000,GPIO_PIN_RESET);
		    //P1000ピンをDIRにつなげる
		    k = 1;
		}
		if(i < 10000){
			//10000回onoffする。W1000PINをPULにつなげる
			 HAL_GPIO_WritePin(GPIOW,GPIO_PIN_1000,GPIO_PIN_SET);
			 HAL_GPIO_WritePin(GPIOW,GPIO_PIN_1000,GPIO_PIN_RESET);
			 i = i + 1;
			 }
		if(i = 10000){
			 HAL_GPIO_WritePin(GPIOQ,GPIO_PIN_1000,GPIO_PIN_RESET);
			 i = i + 1;
			 k = 2;
		}
		if(j < 10000){
		    //10000回onoffする。W1000PINをPULにつなげる
		    HAL_GPIO_WritePin(GPIOW,GPIO_PIN_1000,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOW,GPIO_PIN_1000,GPIO_PIN_RESET);
			j = j + 1;

		}
	    if(j = 10000){
			HAL_GPIO_WritePin(GPIOQ,GPIO_PIN_1000,GPIO_PIN_RESET);
			j = j + 1;
			k = 0;
		}


		if(controller.Up == 1){
			//昇降機構
			//モーター回す
		}
		else if(controller.Down == 1){
			//昇降機構
			//モーター回す
		}
		else{
		    //昇降機構
			//モーター止める
		}



		if(controller.LeftAxisX != 64 || controller.LeftAxisY != 64){

			int x = controller.LeftAxisX;
			int y = controller.LeftAxisY;
			polar_coordinates(x,y);
			moters_power(v,θ);

	}
}
}


extern "C" {
    int pulsePerRotation = 200;

    // millimeter
    double x = 207;
    double y = 97;
    double z = 57;

    enum class HoldType{
        x,
        y,
        z
    }

    double getdistance(HoldType holdType){
        switch (holdType)
        {
        case holdType::x:
            return x;
        case y:
            return y;
        case z:
            return z;
        default:
            return 0;
        }
    }

    int timerThreshold;

    double getTheta(double distance, double radius){
        return distance / radius;
    }
    

    double getMilliseconds(int pulse){
        return 1000 / pulse;
    }

    void getPulse(double theta){
        return pulsePerRotation * theta / ( 2 * PI );
    }

    void setup(){
        timerThreshold = getMilliseconds(getPulse(getTheta()))
    }

    void update(){
        
    }

    void input(){

    }

    void control(){

    }

    void hold(HoldType holdType, int num){
        timerThreshold = getMilliseconds(getPulse(getTheta()))
    }
    
    void release(){

    }

    // Firstly, the holder is closed.
    bool isClosed = true;
    bool isOpened = false;
    bool isClosing = false;
    bool isOpening = false;

    enum class HoldType{
        x,
        y,
        z
    }

    double currentDistance;

    int deltaTime = 1; // milliseconds
    int timer;

    void main_cpp(){
        setup();
        while(){
            update();
            HAL_DELAY(deltaTime);
            timer += deltaTime;
        }
    }
}

