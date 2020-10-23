import sys
import subprocess
import serial
import time


def main():
    hexFile = sys.argv[1]
    executeAvrDude(hexFile)
    readSerial()


def readSerial():
    with serial.Serial('COM4', 57600, timeout=1) as ser:
        while(True):
            # Capture serial output as a decoded string
            val = str(ser.readline().decode().strip('\r\n'))
            valA = val.split("/")
            if "EOF" in val:
                return
            if val != '':
                print(val, end="\n", flush=True)
    # read = ser.read(1)
    # if read != b'':
    #     result = str(read).rstrip().replace('\\n', '\n').replace('\\r', '\r')
    #     if b'\n' in read:
    #         print(result)
    #     else:
    #         print(result, end='')


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
