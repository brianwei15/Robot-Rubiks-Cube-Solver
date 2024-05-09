// these intial variables are basically just for reference now because we ordered the pins so that they were in a loopable pattern

// // defines pins for motor 1
// #define stepPin1 3
// #define dirPin1 4
// #define EN1 2

// // defines pins for motor 2
// #define stepPin2 6
// #define dirPin2 7
// #define EN2 5

// // defines pins for motor 3
// #define stepPin3 9
// #define dirPin3 10
// #define EN3 8

#include <kociemba.h>

char faceAssign[6] = { 'U', 'R', 'F', 'D', 'L', 'B' };  //the character representative of each face

//Kociemba
char cube[1][54] = {
    'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U',  // Up face: white
    'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R',  // Right face: green
    'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F',  // Front face: red
    'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D',  // Down face: yellow
    'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L', 'L',  // Left face: blue
    'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B', 'B'   // Back face: orange
};                //cube defined by the color of each facet denoted as a char: U, R, F, D, L, or B
int numMoves;                    //the number of moves in a solution
String scam[30];                 //array to store solution moves, size set to 30, should not exceed 24

void setup() {
  // // Enables all motors
  // for (int i = 0; i < 6; i++) {
  //   pinMode(3+3*i, OUTPUT);
  //   pinMode(4+3*i, OUTPUT);
  //   pinMode(2+3*i, OUTPUT);
  //   digitalWrite(2+3*i, LOW);
  // }

  Serial.begin(115200);

  //Kociemba
  // em = 0;
  // kociemba::set_memory(buf479, buf248);  // removing this line slows the computation by a factor of 4 (but saves a lot of RAM...)
  for (int i = 0; i < 6; i++) {          //define the color of the middle facets, these are constant
    cube[0][4 + i * 9] = faceAssign[i];
  }
}

void loop() {
  // //motors are marked 1-6 (1: bottom 2: side for now)
  // //first number is motor second number is direction (1: clockwise, 2: counterclockwise)
  // int moves[12] = {11, 21, 31, 41, 51, 61, 10, 20, 30, 40, 50, 60};
  // int size = sizeof(moves)/sizeof(int);
  // chain(moves, size);
  solveCube();
}

// 

//solve the cube with the kociemba algorithm **taken from online source
void solveCube() {
  for (auto s : cube) {
    // em = 0;  //time taken to find a solution
    const char* solution = kociemba::solve(s);
    if (solution == nullptr)
      Serial.println("no solution found");
    else
      Serial.println("Solution: " + String(solution));

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


// void turn(int dir, int motor) {
//   if (dir == 1) digitalWrite(4+3*(motor-1), HIGH); // clockwise
//     else digitalWrite(4+3*(motor-1), LOW); // counterclockwise

//     for (int x = 0; x < 400; x++) {
//       digitalWrite(3+3*(motor-1), HIGH);
//       delayMicroseconds(200);
//       digitalWrite(3+3*(motor-1), LOW);
//       delayMicroseconds(200);
//     }
// }

// void chain(int moves[], int size) {
//   for (int i = 0; i < size; i++) {
//     int motornum = moves[i] / 10;
//     int turndir = moves[i] % 10;
//     turn(turndir, motornum);
//     Serial.print("Motor ");
//     Serial.print(motornum);
//     Serial.print(": ");
//     Serial.println(turndir);
//   }
// }