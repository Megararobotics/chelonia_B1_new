#include <DHT.h> // Include the DHT library for humidity and temperature sensor

#define DHTPIN 25      // Define the digital pin connected to the DHT sensor
#define DHTTYPE DHT11  // Define the type of DHT sensor (DHT11 or DHT22)
DHT dht(DHTPIN, DHTTYPE); // Create a DHT object

// Motor control pins
const int motorAPin1 = 2; // Motor A input pin 1
const int motorAPin2 = 3; // Motor A input pin 2
const int motorBPin1 = 4; // Motor B input pin 1
const int motorBPin2 = 5; // Motor B input pin 2

// PWM enable pins
const int ENa = 9;  // Motor A enable pin (PWM)
const int ENb = 10; // Motor B enable pin (PWM)

// Ultrasonic sensor pins
const int trigPin = 16;
const int echoPin = 17;

// Motor speed (adjustable via PWM)
int motorSpeed = 150; // Speed range: 0-255

void setup() {
  Serial.begin(9600); // Start serial communication for debugging
  dht.begin(); // Start the DHT sensor

  // Set motor control pins as OUTPUT
  pinMode(motorAPin1, OUTPUT);
  pinMode(motorAPin2, OUTPUT);
  pinMode(motorBPin1, OUTPUT);
  pinMode(motorBPin2, OUTPUT);

  // Set PWM enable pins as OUTPUT
  pinMode(ENa, OUTPUT);
  pinMode(ENb, OUTPUT);

  // Set ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Read humidity and temperature from the DHT sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if any reads failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print humidity and temperature values to serial monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");

  // Example motor control: Move forward continuously
  moveForward(motorSpeed);

  // Check for obstacles using ultrasonic sensor
  if (checkObstacle()) {
    // If obstacle detected, stop and turn left
    stopMotors();
    turnLeft(motorSpeed);
    delay(1000); // Adjust as needed for turn duration
  }
}

void moveForward(int speed) {
  // Set motor direction
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorAPin2, LOW);
  digitalWrite(motorBPin1, HIGH);
  digitalWrite(motorBPin2, LOW);

  // Set motor speed using PWM
  analogWrite(ENa, speed);
  analogWrite(ENb, speed);
}

void stopMotors() {
  // Stop both motors
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, LOW);
  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, LOW);

  // Set speed to 0
  analogWrite(ENa, 0);
  analogWrite(ENb, 0);
}

void turnLeft(int speed) {
  // Stop motor A, run motor B to turn left
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, LOW);
  digitalWrite(motorBPin1, HIGH);
  digitalWrite(motorBPin2, LOW);

  // Set speed for motor B
  analogWrite(ENa, 0);
  analogWrite(ENb, speed);
}

bool checkObstacle() {
  // Trigger ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the time it takes for the echo
  long duration = pulseIn(echoPin, HIGH);
  float distance = (duration * 0.0343) / 2; // Calculate distance in cm

  // Print distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm\t");

  // Return true if obstacle is within 10 cm
  if (distance < 10) {
    return true; // Obstacle detected
  } else {
    return false; // No obstacle detected
  }
}
