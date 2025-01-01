// Define motor control pins
const int motor1Dir1 = 2; // Direction input 1 for Motor 1
const int motor1Dir2 = 3; // Direction input 2 for Motor 1
const int motor2Dir1 = 4; // Direction input 1 for Motor 2
const int motor2Dir2 = 5; // Direction input 2 for Motor 2

// Define PWM pins
const int motor1PWM = 9;  // PWM pin for Motor 1
const int motor2PWM = 10; // PWM pin for Motor 2

void setup() {
  // Set motor control pins as OUTPUT
  pinMode(motor1Dir1, OUTPUT);
  pinMode(motor1Dir2, OUTPUT);
  pinMode(motor2Dir1, OUTPUT);
  pinMode(motor2Dir2, OUTPUT);

  // Set PWM pins as OUTPUT
  pinMode(motor1PWM, OUTPUT);
  pinMode(motor2PWM, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    executeCommand(command);
  }
}

void executeCommand(char command) {
  switch (command) {
    case 'B':
      moveForward(150); // Move forward at full speed
      break;
    case 'F':
      moveBackward(150); // Move backward at full speed
      break;
    case 'L':
      moveLeft(150); // Move left at full speed
      break;
    case 'R':
      moveRight(150); // Move right at full speed
      break;
    case 'S':
      stopMotors(); // Stop motors
      break;
    default:
      break;
  }
}

void moveForward(int speed) {
  digitalWrite(motor1Dir1, LOW);
  digitalWrite(motor1Dir2, HIGH);
  digitalWrite(motor2Dir1, LOW);
  digitalWrite(motor2Dir2, HIGH);
  analogWrite(motor1PWM, speed);
  analogWrite(motor2PWM, speed);
}

void moveBackward(int speed) {
  digitalWrite(motor1Dir1, HIGH);
  digitalWrite(motor1Dir2, LOW);
  digitalWrite(motor2Dir1, HIGH);
  digitalWrite(motor2Dir2, LOW);
  analogWrite(motor1PWM, speed);
  analogWrite(motor2PWM, speed);
}

void moveLeft(int speed) {
  digitalWrite(motor1Dir1, LOW);
  digitalWrite(motor1Dir2, HIGH);
  digitalWrite(motor2Dir1, HIGH);
  digitalWrite(motor2Dir2, LOW);
  analogWrite(motor1PWM, speed);
  analogWrite(motor2PWM, speed);
}

void moveRight(int speed) {
  digitalWrite(motor1Dir1, HIGH);
  digitalWrite(motor1Dir2, LOW);
  digitalWrite(motor2Dir1, LOW);
  digitalWrite(motor2Dir2, HIGH);
  analogWrite(motor1PWM, speed);
  analogWrite(motor2PWM, speed);
}

void stopMotors() {
  analogWrite(motor1PWM, 0);
  analogWrite(motor2PWM, 0);
  digitalWrite(motor1Dir1, LOW);
  digitalWrite(motor1Dir2, LOW);
  digitalWrite(motor2Dir1, LOW);
  digitalWrite(motor2Dir2, LOW);
}
