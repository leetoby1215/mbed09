import serial
import time
serdev = '/dev/ttyACM0'
s = serial.Serial(serdev)

for i in range(50):
    s.write(bytes("/LEDControl/run 1 0\r", 'UTF-8'))
    time.sleep(0.5)
    s.write(bytes("/LEDControl/run 0 1\r", 'UTF-8'))
    time.sleep(0.5)

s.close()