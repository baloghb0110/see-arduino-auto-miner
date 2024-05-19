import serial
import time

ser = serial.Serial('COM9', 115200)

def send_command(command):
    ser.write((command + '\n').encode())
    ser.flush()
    
    while True:
        data = ser.readline().decode().strip()
        if data == "done":
            print("Arduino üzenet:", data)
            break
        else:
            print("Arduino üzenet2:", data)

def main():
    time.sleep(2)

    try:
        while True:
            with open('mouse_log.txt', 'r') as file:
                for line in file:
                    send_command(line.strip())
                    time.sleep(0.1)
                
    except KeyboardInterrupt:
        print("Ctrl+C lenyomva. Program leállítva.")
        ser.close()

if __name__ == '__main__':
    main()
