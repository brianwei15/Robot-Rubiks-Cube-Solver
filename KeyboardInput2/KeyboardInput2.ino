// defines pins for the first motor
#define stepPin1 3
#define dirPin1 4
#define EN1 2

// defines pins for the second motor
#define stepPin2 6
#define dirPin2 7
#define EN2 5

void setup() {
  // Sets the six pins as Outputs
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(EN1, OUTPUT);
  digitalWrite(EN1, LOW); // Enables the first motor

  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(EN2, OUTPUT);
  digitalWrite(EN2, LOW); // Enables the second motor

  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    int command = Serial.read();
    interpretCommand(command);
  }
}

void interpretCommand(int command) {
  switch (command) {
    case 'U': // Up arrow
      turn(1, 1); // Example: turn motor 1 clockwise
      break;
    case 'D': // Down arrow
      turn(2, 1); // Example: turn motor 1 counter-clockwise
      break;
    case 'L': // Left arrow
      turn(1, 2); // Example: turn motor 2 clockwise
      break;
    case 'R': // Right arrow
      turn(2, 2); // Example: turn motor 2 counter-clockwise
      break;
    default:
      // Handle other cases or do nothing
      break;
  }
}

void turn(int dir, int motor) {
  if (dir == 1) digitalWrite(4+3*(motor-1), HIGH); // clockwise
    else digitalWrite(4+3*(motor-1), LOW); // counterclockwise

    for (int x = 0; x < 400; x++) {
      digitalWrite(3+3*(motor-1), HIGH);
      delayMicroseconds(200);
      digitalWrite(3+3*(motor-1), LOW);
      delayMicroseconds(200);
    }
}

void chain(int moves[], int size) {
  for (int i = 0; i < size; i++) {
    int motornum = moves[i] / 10;
    int turndir = moves[i] % 10;
    turn(turndir, motornum);
    Serial.print("Motor ");
    Serial.print(motornum);
    Serial.print(": ");
    Serial.println(turndir);
  }
}