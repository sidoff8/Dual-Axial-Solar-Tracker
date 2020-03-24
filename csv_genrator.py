import serial
import numpy as np

l=[]
t = []
h = []
arduinoData = serial.Serial('com14',115200)

count=0
 
    

while True:
    while (arduinoData.inWaiting()==0):
        pass
    arduinoString = arduinoData.readline()
    dataArray = arduinoString.split(',')
    lux = float (dataArray[0] )
    humd = float ( dataArray[1])
    temp = float ( dataArray[2])
    print(lux)
    print(humd)
    print(temp)
    t.append(temp)
    h.append(humd)
    l.append(lux)
    count=count+1
    if(count>60):
        t.pop(0)
        h.pop(0)
        l.pop(0)
