#!/usr/bin/env python
import time
import os
import RPi.GPIO as GPIO
import OSC

# GPIO
GPIO.setmode(GPIO.BCM)
GPIO.cleanup()
DEBUG = 1






# read SPI data from MCP3008 chip, 8 possible adc's (0 thru 7)
def readadc(adcnum, clockpin, mosipin, misopin, cspin):
        if ((adcnum > 7) or (adcnum < 0)):
                return -1
        GPIO.output(cspin, True)

        GPIO.output(clockpin, False) # start clock low
        GPIO.output(cspin, False) # bring CS low

        commandout = adcnum
        commandout |= 0x18 # start bit + single-ended bit
        commandout <<= 3 # we only need to send 5 bits here
        for i in range(5):
                if (commandout & 0x80):
                        GPIO.output(mosipin, True)
                else:
                        GPIO.output(mosipin, False)
                commandout <<= 1
                GPIO.output(clockpin, True)
                GPIO.output(clockpin, False)

        adcout = 0
# read in one empty bit, one null bit and 10 ADC bits
        for i in range(12):
                GPIO.output(clockpin, True)
                GPIO.output(clockpin, False)
                adcout <<= 1
                if (GPIO.input(misopin)):
                        adcout |= 0x1
               
        GPIO.output(cspin, True)

        adcout >>= 1 # first bit is 'null' so drop it
        return adcout

# change these as desired - they're the pins connected from the
# SPI port on the ADC to the RPi
SPICLK = 18
SPIMISO = 23
SPIMOSI = 24
SPICS = 25

# set up the SPI interface pins
GPIO.setup(SPIMOSI, GPIO.OUT)
GPIO.setup(SPIMISO, GPIO.IN)
GPIO.setup(SPICLK, GPIO.OUT)
GPIO.setup(SPICS, GPIO.OUT)

# sensor connected to mcp3008
adc0 = 0;
adc1 = 1;
adc2 = 2;
adc3 = 3;
adc4 = 4;
adc5 = 5;
adc6 = 6;
adc7 = 7;

# Ouput pins
output0 = 4;
output1 = 17;
GPIO.setup(output0, GPIO.OUT)
GPIO.setup(output1, GPIO.OUT)

try:
        while True:

            input0 = readadc(adc0, SPICLK, SPIMOSI, SPIMISO, SPICS)
            input1 = readadc(adc1, SPICLK, SPIMOSI, SPIMISO, SPICS)
            input2 = readadc(adc2, SPICLK, SPIMOSI, SPIMISO, SPICS)
            input3 = readadc(adc3, SPICLK, SPIMOSI, SPIMISO, SPICS)
            input4 = readadc(adc4, SPICLK, SPIMOSI, SPIMISO, SPICS)
            input5 = readadc(adc5, SPICLK, SPIMOSI, SPIMISO, SPICS)
            input6 = readadc(adc6, SPICLK, SPIMOSI, SPIMISO, SPICS)
            input7 = readadc(adc7, SPICLK, SPIMOSI, SPIMISO, SPICS)

            print "input0 : ", input0
            print "input1 : ", input1
            print "input2 : ", input2
            print "input3 : ", input3

            time.sleep(0.1)




except KeyboardInterrupt:
        GPIO.cleanup()

