//edge detection using ir
#define irPin1 22          // IR Sensor 1 connected to digital pin 4
#define irPin2 23          // IR Sensor 2 connected to digital pin 6
#define MLa 2             // Left motor 1st pin
#define MLb 3             // Left motor 2nd pin
#define MRa 4           // Right motor 1st pin
#define MRb 5            // Right motor 2nd pin
#define ENA 9
#define ENB 10

void setup() {
  Serial.begin(9600);
  pinMode(MLa, OUTPUT);    // Set Motor Pins as Outputs
  pinMode(MLb, OUTPUT);
  pinMode(MRa, OUTPUT);
  pinMode(MRb, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(irPin1, INPUT);  // Set IR Sensor Pins as Inputs
  pinMode(irPin2, INPUT);
}

void loop() {
  int irValue1 = digitalRead(irPin1);  // Read IR sensor 1
  int irValue2 = digitalRead(irPin2);  // Read IR sensor 2
  // Both sensors detect edge
  if (irValue1 == LOW && irValue2 == LOW) {
    stopRobot();
    delay(1000);  // Delay for stability
    // Move backward
    moveBackward();
    delay(1000);  // Adjust delay according to your requirement
    // Turn left or right randomly
    if (random(0, 2) == 0) {
      turnLeft();
    } else {
      turnRight();
    }
  }
  // Left sensor detects edge
  else if (irValue1 == LOW) {
    stopRobot();
    delay(1000);  // Delay for stability
    // Move backward
    moveBackward();
    delay(1000);  // Adjust delay according to your requirement
    // Turn right
    turnRight();
  }
  // Right sensor detects edge
  else if (irValue2 == LOW) {
    stopRobot();
    delay(1000);  // Delay for stability
    // Move backward
    moveBackward();
    delay(1000);  // Adjust delay according to your requirement
    // Turn left
    turnLeft();
  }
  // No edge detected, move forward
  else {
    moveForward();
  }
}

// Function to stop the robot
void stopRobot() {
  digitalWrite(MLa, LOW);
  digitalWrite(MLb, LOW);
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// Function to move forward
void moveForward() {
  digitalWrite(MLa, HIGH);
  digitalWrite(MLb, LOW);
  digitalWrite(MRa, HIGH);
  digitalWrite(MRb, LOW);
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
}

// Function to move backward
void moveBackward() {
  digitalWrite(MLa, LOW);
  digitalWrite(MLb, HIGH);
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, HIGH);
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
}

// Function to turn left
void turnLeft() {
  digitalWrite(MLa, LOW);
  digitalWrite(MLb, LOW);
  digitalWrite(MRa, HIGH);
  digitalWrite(MRb, LOW);
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
}

// Function to turn right
void turnRight() {
  digitalWrite(MLa, HIGH);
  digitalWrite(MLb, LOW);
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, LOW);
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
}
