#!/usr/bin/env python3

from periphery import GPIO
import time

Power_Pin = 67  
Start_Pin = 66   

Power_GPIO = GPIO(Power_Pin, "out")
Start_GPIO = GPIO(Start_Pin, "out")

try:
            Power_GPIO.write(True)
            print(f"GSM power ON")
            time.sleep(2)

            Start_GPIO.write(True)
            print(f"GSM start pulse")
            time.sleep(1)
            Start_GPIO.write(False)
            print("GSM start ON")

       
except IOError:
    print("Error")

finally:
    Power_GPIO.close()
    Start_GPIO.close()
