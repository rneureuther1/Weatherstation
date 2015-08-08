
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

while True:
    c = webpage.read(1)
    if not c:
         c = webpage.read(1)
    if not c:
      print "End of file"
      break
    if c=='p':
        if webpage.read(1)=='o':
                if webpage.read(1)=='p':
                        webpage.read(4)
                        firstdigit = webpage.read(1)
                        test = webpage.read(1)
                        if test !="\"":
                            fullnumber=firstdigit+test
                        else:
                            fullnumber=firstdigit
                        print fullnumber


convert = ast.literal_eval(fullnumber)
convert = int(convert)
print "Last digit plus two is %d" %(convert+2)



