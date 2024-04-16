import serial
import keyboard

arduino = serial.Serial('COM3', 9600)

def send_command(key):
    if key.name == 'up':
        arduino.write(b'11')
    elif key.name == 'down':
        arduino.write(b'21')
    elif key.name == 'left':
        arduino.write(b'12')
    elif key.name == 'right':
        arduino.write(b'22')
    elif key.name == 't':
        arduino.write(b't')

keyboard.on_press_key("up", send_command)
keyboard.on_press_key("down", send_command)
keyboard.on_press_key("left", send_command)
keyboard.on_press_key("right", send_command)
keyboard.on_press_key("t", send_command)

# Keep the script running
keyboard.wait('esc')