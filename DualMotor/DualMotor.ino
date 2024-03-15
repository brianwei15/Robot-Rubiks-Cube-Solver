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
  //motors are marked 1-6 (1: bottom 2: side for now)
  //first number is motor second number is direction (1: clockwise, 2: counterclockwise)
  int moves[4] = {11, 21, 10, 20};
  // int moves1[2] = {1};
  // int moves2[1] = {1};
  // int moves3[1] = {0};
  // int moves4[1] = {0};
  int size = sizeof(moves)/sizeof(int);

  // chain(moves1, size, 1); // Chain movements for the first motor
  // chain(moves2, size, 2); // Chain movements for the second motor
  // chain(moves3, size, 1); // Chain movements for the first motor
  chain(moves, size);
}

void turn(int dir, int motor) {
  if (motor == 1) {
    // Control for the first motor
    if (dir == 1) digitalWrite(dirPin, HIGH); // clockwise
    else digitalWrite(dirPin, LOW); // counterclockwise

    for (int x = 0; x < 400; x++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(200);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(200);
    }
  } else if (motor == 2) {
    // Control for the second motor
    if (dir == 1) digitalWrite(dirPin2, HIGH); // clockwise
    else digitalWrite(dirPin2, LOW); // counterclockwise

    for (int x = 0; x < 400; x++) {
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(200);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(200);
    }
  }
  //delay(300); // delay between commands
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