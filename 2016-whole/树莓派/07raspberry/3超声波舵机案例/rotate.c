#include <wiringPi.h>

#include <stdio.h>

#include <unistd.h>

#include <stdlib.h>
#include <sys/time.h>

#define PWM_pin 3        //�����Signal-GPIO 3
#define Trig 4           //��������������Trig��-GPIO 4
#define Echo 5           //��������������Echo��-GPIO 5

int pulsewidth = 0;		 //�ߵ�ƽʱ��

void pulse(int angle)			        //���ö���Ƕ�Ϊangle
{
	pulsewidth=(int)((angle*11)+500);	//����ߵ�ƽʱ��
	digitalWrite(PWM_pin,HIGH);				//���øߵ�ƽ
	delayMicroseconds(pulsewidth);		//��ʱpulsewidth ��us��
	digitalWrite(PWM_pin,LOW);				//���õ͵�ƽ
	delay(20-pulsewidth/1000);	     	//��ʱ20-pulsewidth/1000 ��ms��
}

float disMeasure(void)       //�������
{
	struct timeval tv1;      //����������ʱ��ṹ�������timeval�ṹ��������������Ա������
                                 //tv_sec��tv_usec,�ֱ�������΢�룩
	struct timeval tv2;      //�������״α����ʱ��ṹ�����
	long start, stop;        //���峬��������ʱ����״α����ʱ��
	float dis;               //����������

	digitalWrite(Trig, LOW);
	delayMicroseconds(2);

	digitalWrite(Trig, HIGH);
	delayMicroseconds(10);	  //����һ��10us�ĳ���������
	digitalWrite(Trig, LOW);
	
	while(!(digitalRead(Echo) == 1));  //�ȴ�Echo�˱�Ϊ�ߵ�ƽ
	gettimeofday(&tv1, NULL);		   //��ȡ��ǰʱ�䣬������������ʱ��

	while(!(digitalRead(Echo) == 0));  //����ⲻ��������ʱ����ѭ�����ȴ����ճ�����
	gettimeofday(&tv2, NULL);		   //��ȡ��ǰʱ�䣬���������״α����ʱ��

	start = tv1.tv_sec * 1000000 + tv1.tv_usec;   //΢�뼶�ĳ���������ʱ��
	stop  = tv2.tv_sec * 1000000 + tv2.tv_usec;   //΢�뼶�ĳ������״α����ʱ��

	dis = (float)(stop - start) / 1000000 * 34000 / 2;  //�������

	return dis;
}


int main()
{
	float dis;                         //�������
    if (wiringPiSetup () == -1)   	   //�ж�wiringPi�Ƿ�ɹ���ʼ�������û�У���������
            return 1 ;

    pinMode(PWM_pin,OUTPUT);
	pinMode(Echo,INPUT);
	pinMode(Trig,OUTPUT);

    while(1)
    {      
		int i;
		dis =disMeasure();
		//printf("distance = %0.2f cm\n",dis);
		//����dis�Ĵ�С���ö��ת����ͬ�ĽǶȡ�
		if(dis<10)
			pulse(0);         //���ת��0��
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
				    					  
		delay(100);           //��ʱ0.1s
    }
}