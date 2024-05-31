import cv2
import numpy as np

def split_into_grid(frame, grid_size=(3, 3)):
    """
    Split a frame into a grid of cells.

    Args:
        frame (numpy.ndarray): Input frame (square shape).
        grid_size (tuple): Number of rows and columns in the grid.

    Returns:
        List of numpy.ndarray: List of cells (sub-images) from the grid.
    """
    height, width, _ = frame.shape
    rows, cols = grid_size

    cell_height = height // rows
    cell_width = width // cols

    cells = []
    for r in range(rows):
        for c in range(cols):
            x1, y1 = c * cell_width, r * cell_height
            x2, y2 = (c + 1) * cell_width, (r + 1) * cell_height
            cell = frame[y1:y2, x1:x2]
            cells.append(cell)

    return cells

def draw_grid(frame, grid_size=(3, 3), color=(0, 255, 0), thickness=2):
    """
    Draw grid lines on the input frame.

    Args:
        frame (numpy.ndarray): Input frame (square shape).
        grid_size (tuple): Number of rows and columns in the grid.
        color (tuple): Color of the grid lines (RGB format).
        thickness (int): Thickness of the grid lines.
    
    Returns:
        numpy.ndarray: Frame with grid lines drawn.
    """
    height, width, _ = frame.shape
    rows, cols = grid_size

    cell_height = height // rows
    cell_width = width // cols

    # Draw vertical grid lines
    for c in range(1, cols):
        x = c * cell_width
        cv2.line(frame, (x, 0), (x, height), color, thickness)

    # Draw horizontal grid lines
    for r in range(1, rows):
        y = r * cell_height
        cv2.line(frame, (0, y), (width, y), color, thickness)

    return frame

def get_average_color(cell):
    """
    Calculate the average color (RGB) of the input cell.

    Args:
        cell (numpy.ndarray): Input cell (sub-image).

    Returns:
        tuple: Average color (RGB) as a tuple of integers (R, G, B).
    """
    # Calculate the average color values (RGB) of the cell
    average_color = np.mean(cell, axis=(0, 1)).astype(int)
    return tuple(average_color)

def get_color_name(rgb_color):
    """
    Map the average RGB color to a color name.

    Args:
        rgb_color (tuple): Average color (RGB) as a tuple of integers (R, G, B).

    Returns:
        str: Corresponding color name based on the RGB color.
    """
    # Define color ranges and corresponding color names
    color_ranges = {
        'orange': (np.array([20, 85, 155]), np.array([75, 131, 245])),
        'yellow': (np.array([0, 110, 110]), np.array([83, 185, 220])),
        'blue': (np.array([80, 40, 0]), np.array([170, 130, 100])),
        'green': (np.array([30, 100, 18]), np.array([100, 180, 105])),
        'white': (np.array([90, 110, 120]), np.array([180, 200, 210])),
        'red': (np.array([20, 20, 100]), np.array([80, 93, 240]))
    }

    # Check the average color against predefined color ranges
    for color_name, (lower_bound, upper_bound) in color_ranges.items():
        if np.all(np.logical_and(lower_bound <= rgb_color, rgb_color <= upper_bound)):
            return color_name
    
    return 'unknown'

def convert_to_cube_colors(accumulated_letters):
    """
    Convert accumulated color letters to cube side colors.

    Args:
        accumulated_letters (str): String of accumulated color letters.

    Returns:
        str: String representing cube side colors.
    """
    color_mapping = {
        'B': 'F',  # Blue becomes Front
        'W': 'U',  # White becomes Up
        'G': 'B',  # Green becomes Back
        'R': 'L',  # Red becomes Left
        'O': 'R',  # Orange becomes Right
        'Y': 'D'   # Yellow becomes Down
    }

    # Replace each color letter with its corresponding cube side color
    cube_colors = ''.join([color_mapping.get(letter, '') for letter in accumulated_letters])

    return cube_colors

def main():
    global accumulated_letters
    global colorToSide

    cap = cv2.VideoCapture(0)

    if not cap.isOpened():
        print("Error: Could not open camera.")
        return

    accumulated_letters = ""
    current_letters_grid = [['' for _ in range(3)] for _ in range(3)]  # Initialize grid for current letters

    while True:
        ret, frame = cap.read()

        if not ret:
            print("Error: Failed to capture frame.")
            break

        frame = cv2.flip(frame, 1)

        height, width, _ = frame.shape
        size = min(height, width)
        square_frame = frame[(height - size) // 2:(height + size) // 2,
                             (width - size) // 2:(width + size) // 2]

        cells = split_into_grid(square_frame, grid_size=(3, 3))
        grid_frame = draw_grid(square_frame, grid_size=(3, 3))

        cv2.imshow('Camera with Grid', grid_frame)

        key = cv2.waitKey(1) & 0xFF

        if key == ord('s'):
            current_letters_grid = [['' for _ in range(3)] for _ in range(3)]  # Reset current letters grid

            for r in range(3):
                for c in range(3):
                    cell = cells[r * 3 + c]
                    average_color = get_average_color(cell)
                    color_name = get_color_name(average_color)
                    first_letter = color_name[0].upper()  # Get the first letter and convert to uppercase
                    current_letters_grid[r][c] = first_letter

            print("S to Scan | C to Confirm | R to Remove | Q to Quit")
            for row in current_letters_grid:
                print(' '.join(row))

        elif key == ord('c'):
            # Flatten the grid of letters into a single string and append to accumulated_letters
            current_letters = ''.join([''.join(row[::-1]) for row in current_letters_grid])
            if current_letters:
                match len(accumulated_letters):
                    case 0:
                        current_letters = current_letters[:4] + "W" + current_letters[5:]
                    case 9:
                        current_letters = current_letters[:4] + "O" + current_letters[5:]
                    case 18:
                        current_letters = current_letters[:4] + "B" + current_letters[5:]
                    case 27:
                        current_letters = current_letters[:4] + "Y" + current_letters[5:]
                    case 36:
                        current_letters = current_letters[:4] + "R" + current_letters[5:]
                    case 45:
                        current_letters = current_letters[:4] + "G" + current_letters[5:]
                    case _:
                        pass
                accumulated_letters += current_letters
                print("Output:", accumulated_letters)

        elif key == ord('r'):
            # Remove last 9 letters from accumulated_letters
            accumulated_letters = accumulated_letters[:-9]
            print("Output:", accumulated_letters)

        elif key == ord('q'):
            colorToSide = convert_to_cube_colors(accumulated_letters)
            print("Cube Side Colors:", colorToSide)
            break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    main()

import twophase.solver  as sv

cubestring = colorToSide

#map solution string to string that arduino can read
moves = sv.solve(cubestring, 16, 10)

print(moves)

nummoves = moves[-4:-2] #the number of moves needed to solve the cube
print("num of moves: " + nummoves)
movesstring = moves[:-6] #substring the last part of the string which outputs the number of moves it will take
newmoves = "" #new formatted string

totalturns = 0

#map characters in moves to new string in the format of motornum + move direction
for character in movesstring:
    match character:
        case "U":
            newmoves += "6"
            continue
        case "R":
            newmoves += "2"
            continue
        case "F":
            newmoves += "3"
            continue
        case "D":
            newmoves += "5"
            continue
        case "L":
            newmoves += "4"
            continue
        case "B":
            newmoves += "1"
            continue
        case "1": #clockwise
            newmoves += "0"
            totalturns += 1
            continue
        case "2": #180degrees
            newmoves += "2"
            totalturns += 2
            continue
        case "3": #counterclockwise
            newmoves += "1"
            totalturns += 1
            continue
        case default:
            continue


print(newmoves)
print(totalturns)

# WG
# OW
# BW
# YB
# RW
# GW

#PYTHON CONNECTION PROGRAM USING NEWMOVES

import serial
import time

ser = serial.Serial('COM6', 9600, timeout=1)
time.sleep(2)  

def send_commands(commands):
    """Sends a sequence of commands to the Arduino via serial."""
    for i in range(0, len(commands), 2):
        command = commands[i:i+2] + "\n"
        ser.write(command.encode())

if __name__ == "__main__":
    try:
        send_commands(newmoves)
    except KeyboardInterrupt:
        print("Program terminated.")
        ser.close()