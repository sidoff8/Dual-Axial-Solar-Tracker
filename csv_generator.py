import serial
import csv

arduinoData = serial.Serial('com4',115200)

count=0
with open("C:/Users/Sidharth Singh/Desktop/date27032020.csv", "w") as f1_input:
    fieldnames = ['Irradiance', 'humidity','temp','voltage_dual_axis','current_dual_axis']
    writer = csv.DictWriter(f1_input, fieldnames=fieldnames)
    writer.writeheader()
    while True:
        while (arduinoData.inWaiting()==0):
            pass        
        arduinoString = arduinoData.readline()
        s=arduinoString.decode("UTF-8")
        dataArray = s.split(',')
        lux = float (dataArray[0] )
        humd = float ( dataArray[1])
        temp = float ( dataArray[2])
        volt1=float(dataArray[3])
        curr1= float(dataArray[4])
        print("light Intensity:",end='')
        print(lux,end='')
        print("w/m2   ",end='')
        print("Humidity:",end='')
        print(humd,end='')
        print("%   ",end='')
        print("Temperature:",end='')
        print(temp,end='')
        print("C   ",end='')
        print("Solar Voltage dual axis:",end='')
        print(volt1,end='')
        print("V   ",end='')
        print("Solar Current dual axis:",end='')
        print(curr1,end='')
        print("A   ")
        print("---------------------------------------------------------------------------------------------------------------------------------------------------")
        writer.writerow({'Irradiance': lux ,'humidity': humd, 'temp': temp, 'voltage_dual_axis':volt1,'current_dual_axis':curr1, 'voltage_single_axis':volt2,'current_single_axis':curr2})
        f1_input.flush()

