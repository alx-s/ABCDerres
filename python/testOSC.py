#!/usr/bin/env python
import time
import os
import RPi.GPIO as GPIO
import OSC

# GPIO
GPIO.setmode(GPIO.BCM)
GPIO.cleanup()
DEBUG = 1

# Init OSC
client = OSC.OSCClient()
client.connect(('localhost', 1235))






try:
        while True:
                
            
            

            try:
                client.send(OSC.OSCMessage("/output0", 1))
                time.sleep(1)  
                client.send(OSC.OSCMessage("/output0", 0))
                time.sleep(1)  
                client.send(OSC.OSCMessage("/output1", 1))
                time.sleep(1)  
                client.send(OSC.OSCMessage("/output1", 0))
                time.sleep(1) 
                
                
            except :
                print "not connected"
                pass

        time.sleep(1)        


        
except KeyboardInterrupt:
        GPIO.cleanup()
