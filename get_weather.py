
#!/usr/bin/python
import Adafruit_BBIO.GPIO as GPIO
import time
import json
import urllib
import urllib2
import sys
import ast

webpage = urllib2.urlopen('http://api.wunderground.com/api/5744462c8bb77ed7/hourly/q/28.600000,-81.199997.json')
firstdigit="0"
fullnumber="0"
hourdigit1="0"
hour="0"
hourint=0


startindex=0

t0=int(time.time())
while t0%10!=0:
    t0=int(time.time())
    print t0

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
                        print t0
    # If we come across the "pop" element
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
                        convert = ast.literal_eval(fullnumber)
                        convert = int(convert)
                        print fullnumber







