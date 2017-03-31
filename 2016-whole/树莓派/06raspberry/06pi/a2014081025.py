# this program shows that the leds shine serval times randomly ,
#    which needs you to guess how many leds you see.
# author : ferris chan
# data :2016/10/17
#release :1.0
import RPi.GPIO as GPIO  
import time
import random
pin_list = [17,18,27,22,23,24,25,5,6] 
GPIO.setmode(GPIO.BCM)      # BCM 状态下定义9个引脚
data = int(random.randint(1,9))
pins = pin_list[0:data]     # 随机让几个led灯亮
def setup():                # 设置引脚
    for pin in pins:  
        GPIO.setup(pin, GPIO.OUT)  
        GPIO.output(pin, GPIO.LOW)  
def loop():                 # 点亮led，让其循环亮3次
    while True:  
        for pin in pins:  
            GPIO.output(pin, GPIO.HIGH)  
            time.sleep(0.1)  
            GPIO.output(pin, GPIO.LOW)  
            time.sleep(0.1)
def destroy():
    guess = int(input('how many  shining leds do you see?'))
    if guess == data:     # 猜对则最后一个led亮了
        GPIO.setup(13, GPIO.OUT)
        GPIO.output(13,GPIO.HIGH)
        print('YES!WYSIWYG! The last LED is shining')
        time.sleep(5)         
        GPIO.setup(13, GPIO.IN)
        GPIO.cleanup()
    else:
        print(' GUESS anther number')  # 输入错误，重新输入
        destroy()
    for pin in pin_list:             # 撤销引脚
        GPIO.output(pin, GPIO.LOW)  
        GPIO.setup(pin, GPIO.IN)
setup()
print('please input "CTRL + C" to stop')
try:  
    loop()  
except KeyboardInterrupt:
    destroy()

    

