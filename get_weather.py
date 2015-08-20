""" 
WeatherStation
Reid Neureuther
Summer 2015

Execute on TI Beaglebone Black. Use CronTab to schedule regular calls of this program

"""
#Connect P9_24 to Rx of Trinket
import Adafruit_BBIO.GPIO as GPIO
import time
import json
import urllib
import urllib2
import sys
import ast
import os
import datetime
import serial

# Setup for Serial Tx to Trinket
import Adafruit_BBIO.UART as UART
import serial
import time 
UART.setup("UART1")

# Weather data webpage 
webpage = urllib2.urlopen('http://api.wunderground.com/api/5744462c8bb77ed7/hourly/q/28.600000,-81.199997.json')


try:
    ser = serial.Serial('/dev/tty.usbserial', 9600)
    trinket = serial.Serial(port = "/dev/ttyO1", baudrate=9600)
catch:
    print "Serial Not Available"

trinket.open()

# POP values
firstdigit="0"
fullnumber="0"
POPint="0"
# Hour Values
hourdigit1="0"
hour="0"
hourint=0


startindex=0

ts = time.time()
date = datetime.datetime.fromtimestamp(ts / 1e3)
print date

while True:
    char = webpage.read(1)
    
    # If the end of the file has been reached, stop scanning
    if not char:
      print "End of file"
      break
  
    # When we come across the "hour" element
    if char=='h':
        if webpage.read(1)=='o':
            if webpage.read(1)=='u':
                if webpage.read(1)=='r':
                    if webpage.read(1)=='\"':
                        webpage.read(3)
                        hourdigit1 = webpage.read(1)
                        test=webpage.read(1)
                        if test !="\"":
                            hour=hourdigit1+test
                        else:
                            hour=hourdigit1
                        hourint=ast.literal_eval(hour)
                        hourint=int(hourint)
                        print "The current hour is %d" %hourint
                        trinket.write(hourint)
                   
    # When we come across the "pop" element
    if char=='p':
        if webpage.read(1)=='o':
                if webpage.read(1)=='p':
                        webpage.read(4)
                        firstdigit = webpage.read(1)
                        test = webpage.read(1)
                        if test !="\"":
                            fullnumber=firstdigit+test
                        else:
                            fullnumber=firstdigit
                        POPint = ast.literal_eval(fullnumber)
                        POPint = int(POPint)
                        print POPint
                        trinket.write(POPint)
    
trinket.close()
    





