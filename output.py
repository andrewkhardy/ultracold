import serial
import numpy as np
serial_port = '/dev/ttyUSB0'
baud_rate = 115200
file_path = input("Enter File Name: ") 
ser  = serial.Serial(serial_port,baud_rate)
done = False
data = []
# Here is the reading in of the values
while done == False:
	raw_bytes = ser.readline()
	# read serial value
	decoded_bytes = float(raw_bytes.decode("utf-8"))
	# this line breaks frequently. Just rerun and you'll get it.
	data.append(decoded_bytes)
	if (len(data) > 650) :
		done = True
# actual saving value
np.savetxt(file_path, data, delimiter = ',', fmt='%s')