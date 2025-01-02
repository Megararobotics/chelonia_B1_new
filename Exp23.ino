// Define motor control pins
int motor1A = 2;   // Motor 1 forward
int motor1B = 3;   // Motor 1 backward
int motor2A = 4;   // Motor 2 forward
int motor2B = 5;   // Motor 2 backward

int ENA = 9;       // Enable pin for motor 1 (PWM control)
int ENB = 10;      // Enable pin for motor 2 (PWM control)

int soundSensor = 24; // Pin connected to sound sensor

boolean isMoving = false; // Variable to track whether the robot is moving

void setup() {
  // Setup motor control pins
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);

  // Setup enable pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Setup sound sensor pin
  pinMode(soundSensor, INPUT);
}

void loop() {
  int sensorData = digitalRead(soundSensor); // Read sound sensor data

  if (sensorData == 1) { // Detect a clap
    if (!isMoving) { // If the robot is not moving, start moving forward
      isMoving = true;

      // Set speed using PWM (set to a moderate value, you can change this between 0-255)
      analogWrite(ENA, 150); // Set speed for motor 1
      analogWrite(ENB, 150); // Set speed for motor 2

      // Move forward
      digitalWrite(motor1A, HIGH);
      digitalWrite(motor1B, LOW);
      digitalWrite(motor2A, HIGH);
      digitalWrite(motor2B, LOW);
    } else { // If the robot is moving, stop it
      isMoving = false;

      // Stop the motors
      analogWrite(ENA, 0); // Stop motor 1
      analogWrite(ENB, 0); // Stop motor 2

      digitalWrite(motor1A, LOW);
      digitalWrite(motor1B, LOW);
      digitalWrite(motor2A, LOW);
      digitalWrite(motor2B, LOW);
    }
    delay(500); // Debounce delay to avoid multiple triggers from one clap
  }
}
