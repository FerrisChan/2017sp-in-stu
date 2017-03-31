import RPi.GPIO as GPIO 
import time
channel = 12      
data = []
j = 0
GPIO.setmode(GPIO.BCM)    # BCM的方式，使用GPIO12为DHT11的data接口
time.sleep(1)             # 程序等待1秒
GPIO.setup(channel, GPIO.OUT)  
GPIO.output(channel, GPIO.LOW)
time.sleep(0.02)
# 主机输出一个高电平和一个低电平并延迟，发送开始信号使DHT11工作
GPIO.output(channel, GPIO.HIGH)  # 主机信号为高电平，对应通信过程图使DHT11响应
GPIO.setup(channel, GPIO.IN)     # DHT11开始传输数据给主机
while GPIO.input(channel) == GPIO.LOW:  
    continue
while GPIO.input(channel) == GPIO.HIGH: 
    continue                     # DHT11输入数据
while j < 40:                    # 读取40个数据  
    k = 0
    while GPIO.input(channel) == GPIO.LOW:
        continue                 # DHT11 低电平时等待 
    while GPIO.input(channel) == GPIO.HIGH: # DHT11 读取每一个高电平持续时间，决定数据为0或1
        k += 1
        if k > 100:              # 高电平持续时间过长则跳出循环停止读取，DHT转为低速模式               
            break
    if k < 8:
        data.append(0)           # 当高电平持续时间小于这时间判断 data为 0
    else:
        data.append(1)           # 其他则判断 data 为 1
    j += 1
print ("sensor is working.")
print ( data )
# 读取40个数据：
# 8bit湿度整数数据 +8bit湿度小数数据 +8bi温度整数数据 +8bit温度小数数据 +8bit校验和数据
humidity_bit = data[0:8]
humidity_point_bit = data[8:16]
temperature_bit = data[16:24]
temperature_point_bit = data[24:32]
check_bit = data[32:40]
# 变量初始化 为 0
humidity = 0
humidity_point = 0
temperature = 0
temperature_point = 0
check = 0
# 将 list (data ) 中的数据由二进制转为八进制，并存入相应的变量
for i in range(8):
    humidity += humidity_bit[i] * 2 ** (7 - i)
    humidity_point += humidity_point_bit[i] * 2 ** (7 - i)
    temperature += temperature_bit[i] * 2 ** (7 - i)
    temperature_point += temperature_point_bit[i] * 2 ** (7 - i)
    check += check_bit[i] * 2 ** (7 - i)
tmp = humidity + humidity_point + temperature + temperature_point
# 判断检测和数据是否正确，并显示温度和湿度
if check == tmp:
    print ("temperature : ", temperature, ", humidity : " , humidity)
else:
    print ("wrong")
    print ("temperature : ", temperature, ", humidity : " , humidity, " check : ", check, " tmp : ", tmp)
GPIO.cleanup()
