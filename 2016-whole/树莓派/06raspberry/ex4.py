import RPi.GPIO as GPIO  
import time  
pins = [11,12]  
def setup():  
    GPIO.setmode(GPIO.BOARD)  
    for pin in pins:  
        GPIO.setup(pin, GPIO.OUT)  
        GPIO.output(pin, GPIO.LOW)  
def loop():  
    while True:  
         for pin in pins:  
             GPIO.output(pin, GPIO.HIGH)  
             time.sleep(1)  
             GPIO.output(pin, GPIO.LOW)  
             time.sleep(1) 
def destroy():  
    for pin in pins:  
        GPIO.output(pin, GPIO.LOW)  
        GPIO.setup(pin, GPIO.IN)  
setup()  
try:  
    loop()  
except KeyboardInterrupt:  
    destroy() #树莓电脑大约只能为每个GPIO提供3mA电流

