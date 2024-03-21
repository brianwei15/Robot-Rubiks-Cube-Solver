// defines pins for the first motor
#define stepPin 3
#define dirPin 4
#define EN 2

// defines pins for the second motor
#define stepPin2 6
#define dirPin2 7
#define EN2 5

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
};

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

