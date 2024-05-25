// these intial variables are basically just for reference now because we ordered the pins so that they were in a loopable pattern

void setup() {
  // Enables all motors
  for (int i = 0; i < 6; i++) {
    pinMode(3+3*i, OUTPUT);
    pinMode(4+3*i, OUTPUT);
    pinMode(2+3*i, OUTPUT);
    digitalWrite(2+3*i, LOW);
  }

  // // Sets the six pins as Outputs
  // pinMode(stepPin1, OUTPUT);
  // pinMode(dirPin1, OUTPUT);
  // pinMode(EN1, OUTPUT);
  // digitalWrite(EN1, LOW); // Enables the first motor

  // pinMode(stepPin2, OUTPUT);
  // pinMode(dirPin2, OUTPUT);
  // pinMode(EN2, OUTPUT);
  // digitalWrite(EN2, LOW); // Enables the second motor

  // pinMode(stepPin3, OUTPUT);
  // pinMode(dirPin3, OUTPUT);
  // pinMode(EN3, OUTPUT);
  // digitalWrite(EN3, LOW); // Enables the third motor


  Serial.begin(9600);
}

void loop() {
  //motors are marked 1-6 (1: bottom 2: side for now)
  //first number is motor second number is direction (1: clockwise, 2: counterclockwise)
  int moves[17] = {11, 11, 11, 21, 31, 41, 51, 10, 20, 30, 40, 50, 12, 22, 32, 42, 52};
  int size = sizeof(moves)/sizeof(int);
  chain(moves, size);
}

void turn(int dir, int motor) {
//accounts for clockwise 90 degree, counterclockwise 90 degree, and 180 degree turns
int angle;
  if (dir == 1) {// clockwise
    digitalWrite(4+3*(motor-1), HIGH); 
    angle = 400;
  }
  else if (dir == 2) {// 180
    digitalWrite(4+3*(motor-1), HIGH); 
    angle = 800;
  }
  else {// counterclockwise
    digitalWrite(4+3*(motor-1), LOW); 
    angle = 400;
  }
  for (int x = 0; x < angle; x++) {
      digitalWrite(3+3*(motor-1), HIGH);
      delayMicroseconds(200);
      digitalWrite(3+3*(motor-1), LOW);
      delayMicroseconds(200);
    }
  delay(100);
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