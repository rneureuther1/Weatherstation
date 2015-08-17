#Connect P9_24 to Rx of Photon

import Adafruit_BBIO.UART as UART
import serial
import time 
UART.setup("UART1")
 
ser = serial.Serial(port = "/dev/ttyO1", baudrate=9600)
ser.close()
ser.open()
if ser.isOpen():
    print "Printing Serial"
    ser.write("Hi")
    ser.write("Hi")
    ser.write("Hi")
ser.close()












