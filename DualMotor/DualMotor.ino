// defines pins for the first motor
#define stepPin 3
#define dirPin 4
#define EN 2

// defines pins for the second motor
#define stepPin2 6
#define dirPin2 7
#define EN2 5

void setup() {
  // Sets the six pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW); // Enables the first motor

  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(EN2, OUTPUT);
  digitalWrite(EN2, LOW); // Enables the second motor

  Serial.begin(9600);
}

void loop() {
  int moves1[1] = {1};
  int moves2[1] = {0};
  int size = sizeof(moves1)/sizeof(int);

  chain(moves1, size, 1); // Chain movements for the first motor
  chain(moves2, size, 2); // Chain movements for the second motor
}

void turn(int dir, int motor) {
  if (motor == 1) {
    // Control for the first motor
    if (dir == 1) digitalWrite(dirPin, HIGH); // clockwise
    else digitalWrite(dirPin, LOW); // counterclockwise

    for (int x = 0; x < 400; x++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(500);
    }
  } else if (motor == 2) {
    // Control for the second motor
    if (dir == 1) digitalWrite(dirPin2, HIGH); // clockwise
    else digitalWrite(dirPin2, LOW); // counterclockwise

    for (int x = 0; x < 400; x++) {
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(500);
    }
  }
  delay(500); // delay between commands
}

void chain(int moves[], int size, int motor) {
  for (int i = 0; i < size; i++) {
    turn(moves[i], motor);
    Serial.print("Motor ");
    Serial.print(motor);
    Serial.print(": ");
    Serial.println(moves[i]);
  }
}