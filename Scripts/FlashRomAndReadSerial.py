import sys
import subprocess
import serial
import time


def main():
    if len(sys.argv) == 3:
        hexFile = sys.argv[1]
        port = sys.argv[2]
        executeAvrDude(hexFile, port)
    else:
        port = sys.argv[1]
    readSerial(port)


def readSerial(port):
    with serial.Serial(port, 57600, timeout=1) as ser:
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


def executeAvrDude(filename, port):
    command = [
        r'C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avrdude.exe',
        r'-CC:\Program Files (x86)\Arduino\hardware\tools\avr\etc\avrdude.conf',
        '-v',
        '-patmega328p',
        '-carduino',
        '-P%s' % port,
        '-b115200',
        '-D',
        '-Uflash:w:%s:i' % (filename)
    ]
    returnCode = subprocess.call(command, stderr=subprocess.STDOUT)
    assert returnCode == 0, "Failed to execute avrdude"


if __name__ == "__main__":
    main()
