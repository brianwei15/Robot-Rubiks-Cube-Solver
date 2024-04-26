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
        'orange': (np.array([0, 62, 155]), np.array([58, 120, 230])),
        'yellow': (np.array([0, 110, 130]), np.array([80, 175, 220])),
        'blue': (np.array([80, 40, 0]), np.array([170, 130, 100])),
        'green': (np.array([40, 100, 20]), np.array([100, 180, 95])),
        'white': (np.array([90, 110, 120]), np.array([160, 180, 190])),
        'red': (np.array([20, 20, 140]), np.array([70, 76, 225]))
    }

    # Check the average color against predefined color ranges
    for color_name, (lower_bound, upper_bound) in color_ranges.items():
        if np.all(np.logical_and(lower_bound <= rgb_color, rgb_color <= upper_bound)):
            return color_name
    
    return 'unknown'

def main():
    # Initialize camera capture (0 for default camera)
    cap = cv2.VideoCapture(0)

    if not cap.isOpened():
        print("Error: Could not open camera.")
        return

    while True:
        # Capture frame-by-frame
        ret, frame = cap.read()

        if not ret:
            print("Error: Failed to capture frame.")
            break

        # Flip the frame horizontally
        frame = cv2.flip(frame, 1)

        # Get dimensions of the frame
        height, width, _ = frame.shape

        # Determine the size of the square window (use the minimum dimension)
        size = min(height, width)

        # Crop the frame to a square
        square_frame = frame[(height - size) // 2:(height + size) // 2,
                             (width - size) // 2:(width + size) // 2]

        # Split the square frame into a 3x3 grid of cells
        cells = split_into_grid(square_frame, grid_size=(3, 3))

        # Draw grid lines on the square frame
        grid_frame = draw_grid(square_frame, grid_size=(3, 3))

        # Display the frame with grid lines
        cv2.imshow('Camera with Grid', grid_frame)

        # Check for key press
        key = cv2.waitKey(1) & 0xFF

        if key == ord('s'):
            # Process each grid cell to detect and print color
            for i, cell in enumerate(cells):
                # Calculate the average color of the cell
                average_color = get_average_color(cell)

                # Determine the color name based on the average color
                color_name = get_color_name(average_color)

                # Format RGB values as string
                rgb_str = f"({average_color[0]}, {average_color[1]}, {average_color[2]})"

                # Display the detected color name and RGB values
                print(f"Cell {i}: {color_name.capitalize()} {rgb_str}")

        elif key == ord('q'):  # Press 'q' to quit the program
            break  # Exit the main loop and end the program

    # Release the camera and close all OpenCV windows
    cap.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    main()
