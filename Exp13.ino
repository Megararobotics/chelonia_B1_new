// Define ultrasonic sensor pins
const int trigPin = 16;  // Trig pin of ultrasonic sensor connected to Arduino (D16) 
const int echoPin = 17;  // Echo pin of ultrasonic sensor connected to Arduino (D17)

#define MIN_DISTANCE 10
#define MAX_DISTANCE 30 

// Motor control pins
int LMP = 2;   // Left Motor Positive
int LMN = 3;   // Left Motor Negative
int RMP = 4;   // Right Motor Positive
int RMN = 5;   // Right Motor Negative

// PWM control pins for motors
int ENA = 9;   // PWM pin for Left Motor
int ENB = 10;  // PWM pin for Right Motor

// IR sensor pins
int LSP = 22;  // Left IR Sensor (digital input)
int RSP = 23;  // Right IR Sensor (digital input)

// Declaring the variable duration & distance
long duration;
int distance;  // Variable to store ultrasonic distance

void setup() {
  // Motor pins are OUTPUT
  pinMode(LMP, OUTPUT); // Left Motor Positive
  pinMode(LMN, OUTPUT); // Left Motor Negative
  pinMode(RMP, OUTPUT); // Right Motor Positive
  pinMode(RMN, OUTPUT); // Right Motor Negative

  // PWM pins are OUTPUT
  pinMode(ENA, OUTPUT); // Left Motor PWM
  pinMode(ENB, OUTPUT); // Right Motor PWM

  // IR Sensor pins are INPUT
  pinMode(LSP, INPUT);  // Left IR Sensor
  pinMode(RSP, INPUT);  // Right IR Sensor

  // Ultrasonic Sensor pins 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
 
  Serial.begin(9600);
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = (duration / 2) / 28.5;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
 
  int RSD = digitalRead(RSP);
  Serial.print("RSD: ");  
  Serial.println(RSD);
  delay(250);
  int LSD = digitalRead(LSP);
  Serial.print("LSD: ");  
  Serial.println(LSD);
  delay(250);

  if (distance < 10) { // If the distance of object is less than 10 cm, stop the robot
    // Stops moving the robot
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
    Serial.print("Stop");
    Serial.println();
  }
  // If IR sensor detects an obstacle, its value will be LOW; otherwise, it will be HIGH
  else if (RSD == 0 && LSD == 1) { // If right sensor detects object, turn right
    // Turn Right
    analogWrite(ENA, 150);  // Adjust speed with PWM
    analogWrite(ENB, 100);  // Adjust speed with PWM
    digitalWrite(LMP, HIGH);
    digitalWrite(LMN, LOW);
    digitalWrite(RMP, LOW);
    digitalWrite(RMN, HIGH);
    Serial.print("Right");
    Serial.println();
  }
  else if (RSD == 1 && LSD == 0) { // If left sensor detects object, turn left
    // Turn Left
    analogWrite(ENA, 100);  // Adjust speed with PWM
    analogWrite(ENB, 150);  // Adjust speed with PWM
    digitalWrite(LMP, LOW);
    digitalWrite(LMN, HIGH);
    digitalWrite(RMP, HIGH);
    digitalWrite(RMN, LOW);
    Serial.print("Left");
    Serial.println();
  }
  else if (RSD == 0 && LSD == 0) { // If both sensors detect an object, move forward
    // Move Forward
    analogWrite(ENA, 150);  // Adjust speed with PWM
    analogWrite(ENB, 150);  // Adjust speed with PWM
    digitalWrite(LMP, HIGH);
    digitalWrite(LMN, LOW);
    digitalWrite(RMP, HIGH);
    digitalWrite(RMN, LOW);
    Serial.print("Forward");
    Serial.println();
  }
  else if (distance >= MIN_DISTANCE && distance <= MAX_DISTANCE) { // If distance is between min and max, move forward
    // Move Forward
    analogWrite(ENA, 150);  // Adjust speed with PWM
    analogWrite(ENB, 150);  // Adjust speed with PWM
    digitalWrite(LMP, HIGH);
    digitalWrite(LMN, LOW);
    digitalWrite(RMP, HIGH);
    digitalWrite(RMN, LOW);
    Serial.print("Forward");
    Serial.println();
  }
  else { // Stop the motors
    // Stops moving the robot
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
    Serial.print("Stop");
    Serial.println();
  }
}
