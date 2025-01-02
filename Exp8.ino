//shape forming
// Define motor control pins
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

// Define PWM pins
#define PWM1 9
#define PWM2 10

void setup() {
  // Initialize motor control pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Initialize PWM pins as outputs
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);

  // Initialize serial communication for debugging
  Serial1.begin(9600);
}

void loop() {
  if (Serial1.available()) {
    char command = Serial1.read();

    switch (command) {
      case 'L':
        moveLShape();
        break;
      case 'O':
        moveCircular();
        break;
      default:
        stop();
        break;
    }
  }
}

// Function to move the robot in L-shape
void moveLShape() {
  // Move forward for some distance
  moveForward();
  delay(1000);
  stop();

  // Stop
  stop();
  delay(1000);

  // Turn right
  turnRight();
  delay(700);
  stop();

  // Stop
  stop();
  delay(1000);

  // Move forward again
  moveForward();
  delay(1000);
  stop();
}

// Function to move the robot in a circular motion
void moveCircular() {
  // Rotate the robot clockwise
  rotateClockwise();
}

// Function to move the robot forward
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(PWM1, 200); // Full speed for motor 1
  analogWrite(PWM2, 200); // Full speed for motor 2
}

// Function to stop the robot
void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(PWM1, 0); // Stop motor 1
  analogWrite(PWM2, 0); // Stop motor 2
}

// Function to turn the robot right
void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(PWM1, 190); // Full speed for motor 1
  analogWrite(PWM2, 190); // Full speed for motor 2
}

// Function to rotate the robot clockwise
void rotateClockwise() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(PWM1, 255); // Full speed for motor 1
  analogWrite(PWM2, 255); // Full speed for motor 2

  // Adjust the delay time to control the speed of rotation
  delay(100);
}
