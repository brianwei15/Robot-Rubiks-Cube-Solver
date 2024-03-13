#define stepPin 5
#define dirPin 3
#define EN 6

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    switch (command) {
      case 'R':
        digitalWrite(dirPin, HIGH); 
        makeStep();
        break;
      case 'L':
        digitalWrite(dirPin, LOW);
        makeStep();
        break;
    }
  }
}

void makeStep() {
  
  digitalWrite(stepPin, HIGH);
  delay(1);
  digitalWrite(stepPin, LOW);
  delay(1);
}