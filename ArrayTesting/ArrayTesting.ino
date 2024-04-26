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
  if (Serial.available() > 1) {
    
    int command = Serial.read();
    int command2 = Serial.read();
    interpretCommand(command, command2);
  }
}

void interpretCommand(int command, int command2) {
  int direction=command2=='1'?1:2;
  switch (command) {
    
    case '1': //F
      turn(1, direction); //turn motor 1 clockwise 
      break;
    case '2': //R
      turn(2, direction); //turn motor 1 counter-clockwise
      break;
    case '3': //L
      turn(3, direction); //turn motor 2 clockwise
      break;
    case '4': // B
      turn(4, direction); //turn motor 2 counter-clockwise
      break;
    case '5': // D
      turn(5, direction); //turn motor 2 counter-clockwise
      break;
    case '6': // U
      turn(6, direction); //turn motor 2 counter-clockwise
      break;

    default:
      break;
  }
}

void turn(int motor, int dir) {
  // if (dir == 1) digitalWrite(4+3*(motor-1), HIGH); // clockwise
  //   else digitalWrite(4+3*(motor-1), LOW); // counterclockwise

  //   for (int x = 0; x < 400; x++) {
  //     digitalWrite(3+3*(motor-1), HIGH);
  //     delayMicroseconds(200);
  //     digitalWrite(3+3*(motor-1), LOW);
  //     delayMicroseconds(200);
    Serial.print("Motor ");
    Serial.print(motor);
    Serial.print(": ");
    Serial.println(dir);
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