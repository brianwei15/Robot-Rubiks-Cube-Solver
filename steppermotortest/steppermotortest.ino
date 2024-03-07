/*   
 *   Basic example code for controlling a stepper without library
 *      
 *   by Dejan, https://howtomechatronics.com
 */

// defines pins
#define stepPin 5
#define dirPin 3
#define EN 6

void setup() {
  // Sets the three pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);  // Setting EN to low enables the motor to turn
  Serial.begin(9600);
}
void loop() {
  // turn(true);
  // turn(true);
  // turn(false);
  // turn(false);
  vector <bool> moves = {true, false, true, true, false};
  // bool moves[5] = {true, false, true, true, false};
  chain(moves);
  // digitalWrite(dirPin, HIGH);  // Enables the motor to move in a particular direction
  // // Makes 200 pulses for making one full cycle rotation
  // for (int x = 0; x < 400; x++) {
  //   digitalWrite(stepPin, HIGH);
  //   delayMicroseconds(600);  // by changing this time delay between the steps we can change the rotation speed
  //   digitalWrite(stepPin, LOW);
  //   delayMicroseconds(600);
  // }
  // delay(300);  // One second delay

  // digitalWrite(dirPin, HIGH);  // Enables the motor to move in a particular direction
  // // Makes 200 pulses for making one full cycle rotation
  // for (int x = 0; x < 400; x++) {
  //   digitalWrite(stepPin, HIGH);
  //   delayMicroseconds(600);  // by changing this time delay between the steps we can change the rotation speed
  //   digitalWrite(stepPin, LOW);
  //   delayMicroseconds(600);
  // }
  // delay(300);  // One second delay

  // digitalWrite(dirPin, LOW);  // Enables the motor to move in a particular direction
  // // Makes 200 pulses for making one full cycle rotation
  // for (int x = 0; x < 400; x++) {
  //   digitalWrite(stepPin, HIGH);
  //   delayMicroseconds(600);  // by changing this time delay between the steps we can change the rotation speed
  //   digitalWrite(stepPin, LOW);
  //   delayMicroseconds(600);
  // }
  // delay(300);  // One second delay
}

void turn(bool dir) {
  //90 degree turn
  //True is clockwise (right)
  //Falst is counterclockwise (left)
  if (dir) {
    digitalWrite(dirPin, HIGH);
  }
  else {
    digitalWrite(dirPin, LOW);
  }
  for (int x = 0; x < 400; x++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(600);  // by changing this time delay between the steps we can change the rotation speed
      digitalWrite(stepPin, LOW);
      delayMicroseconds(600);
  }
  delay(200);
}

void chain(bool moves[]) {
  Serial.print(" Size:");
  Serial.print(moves.size());
  for (int i = 0; i < moves.size(); i++) {
    turn(moves[i]);
    Serial.print(moves[i]);
  }
  // for (bool dir: moves) {

  // }
}
  