import sys
import subprocess
import serial
import time


def main():
    if len(sys.argv) == 2:
        hexFile = sys.argv[1]
        executeAvrDude(hexFile)
    readSerial()


def readSerial():
    with serial.Serial('COM4', 57600, timeout=1) as ser:
        while(True):
            # Capture serial output as a decoded string
            recv = ser.readline()
            try:
                val = str(recv.decode().strip('\r\n'))
            except:
                continue
            valA = val.split("/")
            if "EOF" in val:
                print("Received EOF. Exiting...")
                return
            if val != '':
                print(val, end="\n", flush=True)


def executeAvrDude(filename):
    command = [
        r'C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avrdude.exe',
        r'-CC:\Program Files (x86)\Arduino\hardware\tools\avr\etc\avrdude.conf',
        '-v',
        '-patmega328p',
        '-carduino',
        '-PCOM4',
        '-b115200',
        '-D',
        '-Uflash:w:%s:i' % (filename)
    ]
    returnCode = subprocess.call(command, stderr=subprocess.STDOUT)
    assert returnCode == 0, "Failed to execute avrdude"


if __name__ == "__main__":
    main()
