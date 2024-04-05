import serial
import keyboard

# Replace 'COM3' with your Arduino's serial port
arduino = serial.Serial('COM3', 9600)

def send_command(key):
    if key.name == 'up':
        arduino.write(b'U')
    elif key.name == 'down':
        arduino.write(b'D')
    elif key.name == 'left':
        arduino.write(b'L')
    elif key.name == 'right':
        arduino.write(b'R')

keyboard.on_press_key("up", send_command)
keyboard.on_press_key("down", send_command)
keyboard.on_press_key("left", send_command)
keyboard.on_press_key("right", send_command)

# Keep the script running
keyboard.wait('esc')