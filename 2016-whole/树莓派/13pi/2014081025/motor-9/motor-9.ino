#include <Servo.h> 
Servo myservo;  // 创建电机对象
int pos = 0;    // 存放电机旋转角度的变量
int del = 100; // 延时（单位：毫秒）

void setup()
{
Serial.begin(9600);
myservo.attach(9);  // 将伺服电机控制信号连接到在端口9并绑定电机对象
}

void loop() {
// 舵机等待时间 6 hours
  for(int hours = 0; hours <= 5; hours++){
	 for ( int mins =0; mins <= 59; mins ++){
		 for ( int secs = 0; secs <= 59; secs ++){
		 delay(1000);
		 }
	}
  }
  
// 舵机转动时间并转动10次
for (int loopy = 0; loopy<=9; loopy++){
  myservo.write(180);
  delay (1000);
  myservo.write(90);
  delay (1000);
  myservo.write(0);
  delay (3000);
  }
}

