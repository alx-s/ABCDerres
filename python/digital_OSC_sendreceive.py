#!/usr/bin/env python
import time, threading
import os
import RPi.GPIO as GPIO
import OSC

# GPIO
GPIO.setmode(GPIO.BCM)
GPIO.cleanup()
DEBUG = 1

# Init OSC
receive_address = '127.0.0.1', 1235
s = OSC.OSCServer(receive_address) 
s.addDefaultHandlers()

client = OSC.OSCClient()
client.connect(('127.0.0.1', 1234))


# digital pins 
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

# define a message-handler function for the server to call.
def gpioOut0Write_handler(adrr, tags, stuff, source):
    if (stuff[0] != 0):
        GPIO.output(output0, True)
    else:
        GPIO.output(output0, False)

def gpioOut1Write_handler(adrr, tags, stuff, source):
    if (stuff[0] != 0):
        GPIO.output(output1, True)
    else:
        GPIO.output(output1, False)    

# just checking which handlers we have added
print "Registered Callback-functions are :"
for addr in s.getOSCAddressSpace():
    print addr

# Start OSCServer
s.addMsgHandler("/output0", gpioOut0Write_handler)
s.addMsgHandler("/output1", gpioOut1Write_handler)
print "\nStarting OSCServer. Use ctrl-C to quit."
st = threading.Thread( target = s.serve_forever )
st.start()



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

            time.sleep(0.05)    


        
except KeyboardInterrupt:
        GPIO.cleanup()
        s.close()
        st.join()