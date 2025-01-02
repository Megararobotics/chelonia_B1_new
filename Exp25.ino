// Define motor control pins
const int motor1PWM = 9;  // PWM input for Motor 1
const int motor1Dir1 = 2; // Direction input 1 for Motor 1
const int motor1Dir2 = 3; // Direction input 2 for Motor 1

const int motor2PWM = 10;  // PWM input for Motor 2
const int motor2Dir1 = 4; // Direction input 1 for Motor 2
const int motor2Dir2 = 5; // Direction input 2 for Motor 2

void setup() {
  // Set motor control pins as OUTPUT
  pinMode(motor1PWM, OUTPUT);
  pinMode(motor1Dir1, OUTPUT);
  pinMode(motor1Dir2, OUTPUT);

  pinMode(motor2PWM, OUTPUT);
  pinMode(motor2Dir1, OUTPUT);
  pinMode(motor2Dir2, OUTPUT);

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
      moveForward();
      break;
    case 'F':
      moveBackward();
      break;
    case 'L':
      moveLeft();
      break;
    case 'R':
      moveRight();
      break;
    case 'STOP':
      stopMotors();
      break;
    default:
      break;
  }
}

void moveForward() {
  digitalWrite(motor1Dir1, HIGH);
  digitalWrite(motor1Dir2, LOW);
  digitalWrite(motor2Dir1, HIGH);
  digitalWrite(motor2Dir2, LOW);
  analogWrite(motor1PWM, 150);
  analogWrite(motor2PWM, 150);
}

void moveBackward() {
  digitalWrite(motor1Dir1, LOW);
  digitalWrite(motor1Dir2, HIGH);
  digitalWrite(motor2Dir1, LOW);
  digitalWrite(motor2Dir2, HIGH);3
  analogWrite(motor1PWM, 150);
  analogWrite(motor2PWM, 150);
}

void moveLeft() {
  digitalWrite(motor1Dir1, LOW);
  digitalWrite(motor1Dir2, HIGH);
  digitalWrite(motor2Dir1, HIGH);
  digitalWrite(motor2Dir2, LOW);
  analogWrite(motor1PWM, 150);
  analogWrite(motor2PWM, 150);
}

void moveRight() {
  digitalWrite(motor1Dir1, HIGH);
  digitalWrite(motor1Dir2, LOW);
  digitalWrite(motor2Dir1, LOW);
  digitalWrite(motor2Dir2, HIGH);
  analogWrite(motor1PWM, 150);
  analogWrite(motor2PWM, 150);
}

void stopMotors() {
  digitalWrite(motor1Dir1, LOW);
  digitalWrite(motor1Dir2, LOW);
  digitalWrite(motor2Dir1, LOW);
  digitalWrite(motor2Dir2, LOW);
  analogWrite(motor1PWM, 0);
  analogWrite(motor2PWM, 0);
}
