#include <wiringPi.h>

#include <stdio.h>

#include <unistd.h>

#include <stdlib.h>
#include <sys/time.h>

#define PWM_pin 3        //舵机的Signal-GPIO 3
#define Trig 4           //超声波传感器的Trig脚-GPIO 4
#define Echo 5           //超声波传感器的Echo脚-GPIO 5

int pulsewidth = 0;		 //高电平时间

void pulse(int angle)			        //设置舵机角度为angle
{
	pulsewidth=(int)((angle*11)+500);	//计算高电平时间
	digitalWrite(PWM_pin,HIGH);				//设置高电平
	delayMicroseconds(pulsewidth);		//延时pulsewidth （us）
	digitalWrite(PWM_pin,LOW);				//设置低电平
	delay(20-pulsewidth/1000);	     	//延时20-pulsewidth/1000 （ms）
}

float disMeasure(void)       //计算距离
{
	struct timeval tv1;      //超声波发射时间结构体变量（timeval结构体里面有两个成员变量：
                                 //tv_sec和tv_usec,分别代表秒和微秒）
	struct timeval tv2;      //超声波首次被检测时间结构体变量
	long start, stop;        //定义超声波发射时间和首次被检测时间
	float dis;               //定义距离变量

	digitalWrite(Trig, LOW);
	delayMicroseconds(2);

	digitalWrite(Trig, HIGH);
	delayMicroseconds(10);	  //发出一个10us的超声波脉冲
	digitalWrite(Trig, LOW);
	
	while(!(digitalRead(Echo) == 1));  //等待Echo端变为高电平
	gettimeofday(&tv1, NULL);		   //获取当前时间，即超声波发射时间

	while(!(digitalRead(Echo) == 0));  //当检测不到超声波时，空循环，等待接收超声波
	gettimeofday(&tv2, NULL);		   //获取当前时间，即超声波首次被检测时间

	start = tv1.tv_sec * 1000000 + tv1.tv_usec;   //微秒级的超声波发射时间
	stop  = tv2.tv_sec * 1000000 + tv2.tv_usec;   //微秒级的超声波首次被检测时间

	dis = (float)(stop - start) / 1000000 * 34000 / 2;  //求出距离

	return dis;
}


int main()
{
	float dis;                         //定义距离
    if (wiringPiSetup () == -1)   	   //判断wiringPi是否成功初始化，如果没有，跳出程序
            return 1 ;

    pinMode(PWM_pin,OUTPUT);
	pinMode(Echo,INPUT);
	pinMode(Trig,OUTPUT);

    while(1)
    {      
		int i;
		dis =disMeasure();
		//printf("distance = %0.2f cm\n",dis);
		//根据dis的大小，让舵机转到不同的角度。
		if(dis<10)
			pulse(0);         //舵机转到0度
		else if(dis<20)
			pulse(20);
		else if(dis<30)
            pulse(40);
	    else if(dis<40)
		    pulse(60);
		else if(dis<50)
		    pulse(80);
		else if(dis<60)
		    pulse(100);
		else if(dis<70)
		    pulse(120);
		else if(dis<80)
		    pulse(140);
		else if(dis<90)
		    pulse(160);
		else
			pulse(180);
				    					  
		delay(100);           //延时0.1s
    }
}