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