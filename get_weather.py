
#!/usr/bin/python
import Adafruit_BBIO.GPIO as GPIO
import time
import json
import urllib
import urllib2
import sys

webpage = urllib2.urlopen('http://api.wunderground.com/api/5744462c8bb77ed7/hou$
print "First Read"
print webpage.read(3)
print "Second Read"
print webpage.read(10)
print "Third Read"
print webpage.read(20)

print sys.getsizeof(webpage)

while True:
    c = webpage.read(1)
    if not c:
      print "End of file"
      break
    if c=='p':
        if webpage.read(1)=='o':
                if webpage.read(1)=='p':
                        print webpage.read(7)




