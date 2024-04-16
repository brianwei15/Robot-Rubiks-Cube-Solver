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

class Turn {
  public:
    int motorNum; // Motor identifier
    int turnDir;  // Direction of turn: 1 for clockwise, -1 for counterclockwise

    // Constructor for initializing the motor attributes
    Turn(int num, int dir) : motorNum(num), turnDir(dir) {}

    // Method to display motor details on the Serial Monitor
    void display() {
      Serial.print("Motor Number: ");
      Serial.print(motorNum);
      Serial.print(", Turn Direction: ");
      Serial.println(turnDir);
    }

    // Add additional methods to control the motor here
    void turn() {
      if (turnDir == 1) digitalWrite(4+3*(motorNum-1), HIGH); // clockwise
        else digitalWrite(4+3*(motorNum-1), LOW); // counterclockwise

        for (int x = 0; x < 400; x++) {
          digitalWrite(3+3*(motorNum-1), HIGH);
          delayMicroseconds(200);
          digitalWrite(3+3*(motorNum-1), LOW);
          delayMicroseconds(200);
        }
    }
};

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

  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);
  pinMode(EN3, OUTPUT);
  digitalWrite(EN3, LOW); // Enables the third motor


  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Turn turn1(1, 1);
  turn1.display();
  Turn turn2(2, 1);
  turn2.display();
  Turn turn3(1, 0);
  turn3.display();
  Turn turn4(2, 0);
  turn4.display();
  Turn moves[4] = {turn1, turn2, turn3, turn4};
  Serial.print("Hello");

}

