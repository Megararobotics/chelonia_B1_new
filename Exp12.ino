// Define IR sensor pins
const int irSensorPin1 = 23; // Use digital pin 23 for the IR sensor1
const int irSensorPin2 = 22; // Use digital pin 22 for the IR sensor2
// Define motor control pins
const int IN1 = 2;  // Motor A control pin 1
const int IN2 = 3;  // Motor A control pin 2
const int IN3 = 4;  // Motor B control pin 1
const int IN4 = 5;  // Motor B control pin 2
const int ENA = 9;  // Motor A PWM pin
const int ENB = 10; // Motor B PWM pin

void setup() {
  Serial.begin(9600); // Start serial communication

  // Set IR sensor pins as INPUT
  pinMode(irSensorPin1, INPUT);
  pinMode(irSensorPin2, INPUT);

  // Set motor control pins as OUTPUT
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  // Read IR sensor values
  int irSensorValue1 = digitalRead(irSensorPin1);
  int irSensorValue2 = digitalRead(irSensorPin2);

  // Check if either IR sensor detects an obstacle
  if (irSensorValue1 == LOW || irSensorValue2 == LOW) { // Assuming LOW indicates an obstacle
    // Obstacle detected by any sensor, stop the motors
    stopMotors();
    Serial.println("Obstacle detected by one or more sensors! Stopping motors.");
  } else {
    // No obstacle detected by any sensor, move forward
    moveForward();
    Serial.println("No obstacle detected. Moving forward.");
  }
}

// Function to stop the motors
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); // Stop motor A
  analogWrite(ENB, 0); // Stop motor B
}

// Function to move forward
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 150); // Set motor A to medium speed
  analogWrite(ENB, 150); // Set motor B to medium speed
}
