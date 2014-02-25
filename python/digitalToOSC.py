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
client.connect(('localhost', 1234))


# digital input 
out0 = 4;
out1 = 17;
in0 = 27;
in1 = 22;
in2 = 18;
in3 = 23;
in4 = 24;
in5 = 25;

# set up the gpio
GPIO.setup(out0, GPIO.OUT)
GPIO.setup(out1, GPIO.OUT)
GPIO.setup(in0, GPIO.IN)
GPIO.setup(in1, GPIO.IN)
GPIO.setup(in2, GPIO.IN)
GPIO.setup(in3, GPIO.IN)
GPIO.setup(in4, GPIO.IN)
GPIO.setup(in5, GPIO.IN)




try:
        while True:
                
            input0 = GPIO.input(in0)
            input1 = GPIO.input(in1)
            input2 = GPIO.input(in2)
            input3 = GPIO.input(in3)
            input4 = GPIO.input(in4)
            input5 = GPIO.input(in5)
            

            try:
                client.send(OSC.OSCMessage("input0", input0))
                client.send(OSC.OSCMessage("input1", input1))
                client.send(OSC.OSCMessage("input2", input2))
                client.send(OSC.OSCMessage("input3", input3))
                client.send(OSC.OSCMessage("input4", input4))
                client.send(OSC.OSCMessage("input5", input5))
                
            except :
                print "not connected"
                pass


        
except KeyboardInterrupt:
        GPIO.cleanup()
