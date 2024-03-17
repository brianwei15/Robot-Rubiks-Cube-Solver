/*   
 *   Basic example code for controlling a stepper without library
 *      
 *   by Dejan, https://howtomechatronics.com
 */

// defines pins
// #define stepPin 5
// #define dirPin 3
// #define EN 6

#define stepPin1 3
#define dirPin1 4
#define EN1 2

// #define stepPin2 6
// #define dirPin2 7
// #define EN2 5

void setup() {
  // Sets the three pins as Outputs
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(EN1, OUTPUT);
  digitalWrite(EN1, LOW);  // Setting EN to low enables the motor to turn
  Serial.begin(9600);
}

void loop() {
  int moves[5] = {1, 0, 1, 1, 0};
  int size = sizeof(moves)/sizeof(int);
  chain(moves, size);
}

void turn(int dir) {
  //1 is clockwise (right)
  //0 is counterclockwise (left)
  if (dir == 1) {
    digitalWrite(dirPin1, HIGH); // clockwise
  }
  else {
    digitalWrite(dirPin1, LOW); // counterclockwise
  }
  // 405 pulses for 90 degree turn
  for (int x = 0; x < 405; x++) {
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(200);  // by changing this time delay between the steps we can change the rotation speed
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(200);
  }
  delay(300); // 0.2 second delay
}

void chain(int moves[], int size) {
  for (int i = 0; i < size; i++) {
    turn(moves[i]);
    Serial.print(moves[i]);
  }
}