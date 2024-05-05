// these intial variables are basically just for reference now because we ordered the pins so that they were in a loopable pattern

// defines pins for motor 1
#define stepPin1 3
#define dirPin1 4
#define EN1 2

// defines pins for motor 2
#define stepPin2 6
#define dirPin2 7
#define EN2 5

// defines pins for motor 3
#define stepPin3 9
#define dirPin3 10
#define EN3 8

#include <kociemba.h>

void setup() {
  // Enables all motors
  for (int i = 0; i < 6; i++) {
    pinMode(3+3*i, OUTPUT);
    pinMode(4+3*i, OUTPUT);
    pinMode(2+3*i, OUTPUT);
    digitalWrite(2+3*i, LOW);
  }

  Serial.begin(9600);
}

void loop() {
  // //motors are marked 1-6 (1: bottom 2: side for now)
  // //first number is motor second number is direction (1: clockwise, 2: counterclockwise)
  // int moves[12] = {11, 21, 31, 41, 51, 61, 10, 20, 30, 40, 50, 60};
  // int size = sizeof(moves)/sizeof(int);
  // chain(moves, size);
  solveCube();
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

//solve the cube with the kociemba algorithm **taken from online source
void solveCube() {
  for (auto s : cube) {
    em = 0;  //time taken to find a solution
    const char* solution = kociemba::solve(s);
    if (solution == nullptr)
      Serial.println("no solution found");
    else
      Serial.printf("Solution: %s \n", solution);
    //convert solution to an array of moves
    numMoves = 0;
    for (int i = 0; i < ((String)solution).length(); i++) {
      scam[numMoves] = solution[i++];                     //set move initially
      while (solution[i] != 32) {                         //32 is ascii for a single space
        scam[numMoves] = scam[numMoves] + solution[i++];  //add on the parts of the move
      }
      numMoves++;
    }
  }
}