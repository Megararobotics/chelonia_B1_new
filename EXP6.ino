#include <MPU6050_light.h>
#include <Wire.h>

// Initialize the IMU
MPU6050 mpu(Wire);


// Define the motor control pins based on your setup
#define IN_1  2        // L298N #1, IN4 for Front Right motor
#define IN_2  3        // L298N #1, IN3 for Front Right motor
#define IN_3  4        // L298N #1, IN2 for Front Left motor
#define IN_4  5        // L298N #1, IN1 for Front Left motor
#define EN_A   9       // Enable pin for L298N #1 (Front motors)
#define EN_B   10      // Enable pin for L298N #1 (Front motors)

void setup() {
  Wire.begin();
  mpu.begin();
  mpu.calcGyroOffsets(); // Calibrate the gyro, hold the robot still during calibration

  // Initialize motor control pins as outputs
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);

  Serial.begin(9600);    // Initialize Serial communication for debugging
}

void loop() {
  mpu.update();  // Update IMU data

  // Move forward
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);

  // Enable all motors
  analogWrite(EN_A, 100); // Full speed for front motors
  analogWrite(EN_B, 100); // Full speed for front motors

  // Send IMU data to Bluetooth Serial Monitor app
  Serial.print("Angle X: ");
  Serial.print(mpu.getAngleX());
  Serial.print(" | Angle Y: ");
  Serial.print(mpu.getAngleY());
  Serial.print(" | Angle Z: ");
  Serial.println(mpu.getAngleZ());

  delay(100);  // Short delay to stabilize readings
}
