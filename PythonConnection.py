import serial
import time


ser = serial.Serial('/dev/cu.usbserial-10', 9600, timeout=1)
time.sleep(2)  

def send_commands(commands):
    """Sends a sequence of commands to the Arduino via serial."""
    for i in range(0, len(commands), 2):
        command = commands[i:i+2] + "\n"
        ser.write(command.encode())

if __name__ == "__main__":
    try:
        commands = input("Enter a sequence of commands (e.g., '11226132' for motor 1 CW, motor 2 CCW, motor 1 CW, motor 3 CCW): ")
        send_commands(commands)
    except KeyboardInterrupt:
        print("Program terminated.")
        ser.close()