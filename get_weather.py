
#!/usr/bin/python
import Adafruit_BBIO.GPIO as GPIO
import time
import json
import urllib
import urllib2
import sys
import ast

webpage = urllib2.urlopen('http://api.wunderground.com/api/5744462c8bb77ed7/hou$
firstdigit="0"
seconddigit="0"

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
                        print firstdigit
                        test = webpage.read(1)
                        if test !="\"":
                                seconddigit=firstdigit+test
                                print seconddigit

convert = ast.literal_eval(seconddigit)
convert = int(convert)
convert = ast.literal_eval(seconddigit)
convert = int(convert)
print "Last digit plus two is %d" %(convert+2)



