// Define motor pins
#define IN_11  2        // L298N #1 in 4 motor Front Right
#define IN_12  3        // L298N #1 in 3 motor Front Right
#define IN_13  4        // L298N #1 in 2 motor Front Left
#define IN_14  5        // L298N #1 in 1 motor Front Left
#define EN_1   9        // Enable pin for Front motors
#define EN_2   10       // Enable pin for Front motors

// Speed variable
int speedValue = 0;

void setup() {
  // Initialize motor pins
  pinMode(IN_11, OUTPUT);
  pinMode(IN_12, OUTPUT);
  pinMode(IN_13, OUTPUT);
  pinMode(IN_14, OUTPUT);
  pinMode(EN_1, OUTPUT);
  pinMode(EN_2, OUTPUT);


  // Start serial communication
  Serial.begin(9600);

  // Stop motors initially
  stopMotors();
}

void loop() {
  if (Serial.available() > 0) {
    // Read the incoming speed value
    speedValue = Serial.parseInt();

    // If speedValue is greater than 0, move forward
    if (speedValue > 0) {
      moveForward(speedValue);
    } else {
      stopMotors();
    }
  }
}

// Function to move the robot forward
void moveForward(int speed) {
  // Front Right Motor
  analogWrite(EN_1, speed);
  digitalWrite(IN_11, HIGH);
  digitalWrite(IN_12, LOW);

  // Front Left Motor
  analogWrite(EN_2, speed);
  digitalWrite(IN_13, HIGH);
  digitalWrite(IN_14, LOW);


}

// Function to stop the robot
void stopMotors() {
  // Stop Front Right Motor
  analogWrite(EN_1, 0);
  digitalWrite(IN_11, LOW);
  digitalWrite(IN_12, LOW);

  // Stop Front Left Motor
  analogWrite(EN_2, 0);
  digitalWrite(IN_13, LOW);
  digitalWrite(IN_14, LOW);




}
