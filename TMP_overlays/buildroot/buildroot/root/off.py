#!/usr/bin/env python3

from periphery import GPIO
import time
 
Power_Pin = 67  
Start_Pin = 66   

Power_GPIO = GPIO(Power_Pin, "out")
Start_GPIO = GPIO(Start_Pin, "out")

try:
        

            Start_GPIO.write(True)
            print(f"GSM start pulse")
            time.sleep(1)
            Start_GPIO.write(False)
            print("GSM start OFF")

            time.sleep(5)
            Power_GPIO.write(False)
            print("GSM OFF")

       
except IOError:
    print("Error")

finally:
    Power_GPIO.close()
    Start_GPIO.close()
