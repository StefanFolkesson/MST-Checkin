import RPi.GPIO as GPIO
from time import sleep
import sys

#Function
def ByteAsArray(x):
        d = [0,0,0,0,0,0,0,0]
        i = 0
        while i < 8:
                d[7 - i] = (x >> i) & 1
                i = i + 1
        return d;



#GPIO Setup
wake_pin = 23
data_pin = 24
clock_pin = 25

GPIO.setmode(GPIO.BCM)
GPIO.setup(wake_pin, GPIO.OUT)
GPIO.setup(data_pin, GPIO.OUT)
GPIO.setup(clock_pin, GPIO.OUT)


#Get arguments


send_c = ByteAsArray(int(sys.argv[1]))
send_r = ByteAsArray(int(sys.argv[2]))
send_g = ByteAsArray(int(sys.argv[3]))
send_b = ByteAsArray(int(sys.argv[4]))


#Wake indicator by interupt
GPIO.output(wake_pin, True)
sleep(0.1)
GPIO.output(wake_pin, False)
sleep(0.01)


#Send command byte
i = 0
while i < 8:
        GPIO.output(data_pin,send_c[i])
        GPIO.output(clock_pin, True)
        sleep(0.01)
        GPIO.output(clock_pin, False)
        sleep(0.01)
        i = i + 1
		
#Send Red byte
i = 0
while i < 8:
        GPIO.output(data_pin,send_r[i])
        GPIO.output(clock_pin, True)
        sleep(0.01)
        GPIO.output(clock_pin, False)
        sleep(0.01)
        i = i + 1

		
#Send Green byte
i = 0
while i < 8:
        GPIO.output(data_pin,send_g[i])
        GPIO.output(clock_pin, True)
        sleep(0.01)
        GPIO.output(clock_pin, False)
        sleep(0.01)
        i = i + 1

#Send Blue byte
i = 0
while i < 8:
        GPIO.output(data_pin,send_b[i])
        GPIO.output(clock_pin, True)
        sleep(0.01)
        GPIO.output(clock_pin, False)
        sleep(0.01)
        i = i + 1

#Release GPIO pins
GPIO.cleanup()
		

