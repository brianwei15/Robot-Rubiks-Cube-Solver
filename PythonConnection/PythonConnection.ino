void setup() {
  // Enables all six motors
  for (int i = 0; i < 6; i++) {
    pinMode(3 + 3 * i, OUTPUT);
    pinMode(4 + 3 * i, OUTPUT);
    pinMode(2 + 3 * i, OUTPUT);
    digitalWrite(2 + 3 * i, LOW);
  }

  Serial.begin(9600);
}

void loop() {
  // This loop now just waits for incoming serial data.
}

void serialEvent() {
  while (Serial.available()) {
    int command = Serial.parseInt(); // Read integer command from Serial
    if (command != 0) {
      int motor = command / 10;
      int dir = command % 10;
      turn(dir, motor);
      Serial.print("Motor ");
      Serial.print(motor);
      Serial.print(": ");
      Serial.println(dir == 1 ? "clockwise" : "counterclockwise");
    }
  }
}

// void turn(int dir, int motor) {
//   int stepPin = 3 + 3 * (motor - 1);
//   int dirPin = 4 + 3 * (motor - 1);

//   digitalWrite(dirPin, dir == 1 ? HIGH : LOW); // Set direction

//   for (int x = 0; x < 400; x++) { // Perform steps
//     digitalWrite(stepPin, HIGH);
//     delayMicroseconds(200);
//     digitalWrite(stepPin, LOW);
//     delayMicroseconds(200);
//   }
//   delay(200);
// }

void turn(int dir, int motor) {
//accounts for clockwise 90 degree, counterclockwise 90 degree, and 180 degree turns
int angle;
  if (dir == 1) {// clockwise
    digitalWrite(4+3*(motor-1), LOW); 
    angle = 400;
  }
  else if (dir == 2) {// 180
    digitalWrite(4+3*(motor-1), HIGH); 
    angle = 800;
  }
  else {// counterclockwise
    digitalWrite(4+3*(motor-1), HIGH); 
    angle = 400;
  }
  for (int x = 0; x < angle; x++) {
      digitalWrite(3+3*(motor-1), HIGH);
      delayMicroseconds(200);
      digitalWrite(3+3*(motor-1), LOW);
      delayMicroseconds(200);
    }
    // delay(20);
}