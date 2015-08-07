
#!/usr/bin/python
import Adafruit_BBIO.GPIO as GPIO
import time
import json
import urllib


try:
	webpage = urlopen('http://api.wunderground.com/api/5744462c8bb77ed7/hourly/q/28.600000,-81.199997.json')
	print webpage
	
except:
	print "Cannot Access Webpage"

