// Define motor control pins
int ENA = 9;  // PWM pin for motor 1 (speed control)
int ENB = 10; // PWM pin for motor 2 (speed control)
int IN1 = 2;  // Motor 1 direction input 1
int IN2 = 3;  // Motor 1 direction input 2
int IN3 = 4;  // Motor 2 direction input 1
int IN4 = 5;  // Motor 2 direction input 2

char command;  // Variable to store the received command via Bluetooth

void setup() {
  // Set motor control pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Initialize Serial communication for Bluetooth (9600 baud rate)
  Serial.begin(9600);
}

void loop() {
  // Check if data is received via Bluetooth
  if (Serial.available() > 0) {
    command = Serial.read();  // Read the incoming command
    
    // Control the motors based on the received command
    switch (command) {
      case 'F':  // Move Forward
        moveForward();
        break;
      case 'B':  // Move Backward
        moveBackward();
        break;
      case 'L':  // Turn Left
        turnLeft();
        break;
      case 'R':  // Turn Right
        turnRight();
        break;
      case 'S':  // Stop
        stopMotors();
        break;
    }
  }
}

// Function to move forward
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 150);  
  analogWrite(ENB, 150);  
}

// Function to move backward
void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 150);  
  analogWrite(ENB, 150);  
}

// Function to turn left
void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 150);  
  analogWrite(ENB, 150);  
}

// Function to turn right
void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 150);  
  analogWrite(ENB, 150);  
}

// Function to stop the motors
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
