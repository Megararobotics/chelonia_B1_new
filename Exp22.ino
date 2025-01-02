#include <NewPing.h>
 
#define LEFT_TRIG_PIN 14
#define LEFT_ECHO_PIN 15
#define FRONT_TRIG_PIN 16
#define FRONT_ECHO_PIN 17
#define RIGHT_TRIG_PIN 18
#define RIGHT_ECHO_PIN 19
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
 
NewPing leftSensor(LEFT_TRIG_PIN, LEFT_ECHO_PIN, MAX_DISTANCE);
NewPing frontSensor(FRONT_TRIG_PIN, FRONT_ECHO_PIN, MAX_DISTANCE);
NewPing rightSensor(RIGHT_TRIG_PIN, RIGHT_ECHO_PIN, MAX_DISTANCE);
 
const int LEFT_MOTOR_IN1 = 2;  // Define the pins for controlling left motor direction
const int LEFT_MOTOR_IN2 = 3;  // Added a corrected direction pin for left motor
const int RIGHT_MOTOR_IN1 = 4; // Define the pins for controlling right motor direction
const int RIGHT_MOTOR_IN2 = 5;

const int ENA = 9;  // Enable pin for left motor (PWM control)
const int ENB = 10; // Enable pin for right motor (PWM control)
 
void setup() {
  Serial.begin(9600);
  pinMode(LEFT_MOTOR_IN1, OUTPUT); // Set motor driver pins as outputs
  pinMode(LEFT_MOTOR_IN2, OUTPUT);
  pinMode(RIGHT_MOTOR_IN1, OUTPUT);
  pinMode(RIGHT_MOTOR_IN2, OUTPUT);
  
  pinMode(ENA, OUTPUT); // Enable pin for PWM control of left motor
  pinMode(ENB, OUTPUT); // Enable pin for PWM control of right motor
}
 
void loop() {
  int leftDistance = leftSensor.ping_cm();
  int frontDistance = frontSensor.ping_cm();
  int rightDistance = rightSensor.ping_cm();
 
  if (leftDistance > 0 && rightDistance > 0 && frontDistance > 0) {
    if (frontDistance < 20) { // If obstacle in front
      if (leftDistance > rightDistance) {
        // Turn left
        turnLeft();
      } else {
        // Turn right
        turnRight();
      }
    } else {
      // Move forward
      moveForward();
    }
  }
}
 
void moveForward() {
  // Set speed of the motors (PWM value between 0-255)
  analogWrite(ENA, 150); // Speed control for left motor
  analogWrite(ENB, 150); // Speed control for right motor

  // Control the motors to move the robot forward
  digitalWrite(LEFT_MOTOR_IN1, HIGH);
  digitalWrite(LEFT_MOTOR_IN2, LOW);
  digitalWrite(RIGHT_MOTOR_IN1, HIGH);
  digitalWrite(RIGHT_MOTOR_IN2, LOW);
}
 
void turnLeft() {
  // Set speed of the motors (PWM value between 0-255)
  analogWrite(ENA, 150); // Speed control for left motor
  analogWrite(ENB, 150); // Speed control for right motor

  // Control the motors to turn left
  digitalWrite(LEFT_MOTOR_IN1, LOW);
  digitalWrite(LEFT_MOTOR_IN2, HIGH);
  digitalWrite(RIGHT_MOTOR_IN1, HIGH);
  digitalWrite(RIGHT_MOTOR_IN2, LOW);
}
 
void turnRight() {
  // Set speed of the motors (PWM value between 0-255)
  analogWrite(ENA, 150); // Speed control for left motor
  analogWrite(ENB, 150); // Speed control for right motor

  // Control the motors to turn right
  digitalWrite(LEFT_MOTOR_IN1, HIGH);
  digitalWrite(LEFT_MOTOR_IN2, LOW);
  digitalWrite(RIGHT_MOTOR_IN1, LOW);
  digitalWrite(RIGHT_MOTOR_IN2, HIGH);
}
