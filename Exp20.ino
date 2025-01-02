// defines ultrasonic sensor pins
const int trigPin = 16;
const int echoPin = 17;

// Left Motor connected to 2,3 digital pins
int LMP = 2; // Left motor positive
int LMN = 3; // Left motor negative
// Right Motor connected to 4,5 digital pins
int RMP = 4; // Right motor positive
int RMN = 5; // Right motor negative

// Left sensors on digital pin 22, 23
int LSP = 22; // Left sensor pin
int RSP = 23; // Right sensor pin

// Enable pins for motor speed control
int ENA = 9;  // Enable pin for left motor (PWM control)
int ENB = 10; // Enable pin for right motor (PWM control)

// Initial Values of Sensors
int sensor[2] = {0, 0};

// defines variables
long duration, distance;
String A, B, C, D;

void setup() 
{
  // Motor pins are OUTPUT
  pinMode(LMP, OUTPUT); // Left motor
  pinMode(LMN, OUTPUT); // Left motor
  pinMode(RMP, OUTPUT); // Right motor
  pinMode(RMN, OUTPUT); // Right motor
  pinMode(ENA, OUTPUT); // Enable pin for left motor (PWM)
  pinMode(ENB, OUTPUT); // Enable pin for right motor (PWM)

  // IR Sensor pins are INPUT
  pinMode(LSP, INPUT); // Left IR Sensor
  pinMode(RSP, INPUT); // Right IR Sensor

  // ultrasonic sensor
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);

  Serial.begin(9600);   // setting serial monitor at a default baud rate of 9600
}

void loop() 
{ 
  // Ultrasonic sensor measurement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Calculate distance
  Serial.print("Distance: ");
  Serial.println(distance);
  
  // Read sensor data and store it
  int LSD = digitalRead(LSP);
  Serial.print("LSD: ");  
  Serial.println(LSD);
  delay(250);
  int RSD = digitalRead(RSP);
  Serial.print("RSD: ");  
  Serial.println(RSD);
  delay(250);

  if (distance > 15) // If distance > 15 cm, proceed with movement
  {
    if (LSD == 0 && RSD == 0) // If both sensors are not on the black line (0), move forward
    {
      // Moves Forward
      analogWrite(ENA, 150); // Set speed for left motor (PWM value between 0-255)
      analogWrite(ENB, 150); // Set speed for right motor (PWM value between 0-255)
      digitalWrite(LMP, HIGH); // Left motor forward
      digitalWrite(LMN, LOW);
      digitalWrite(RMP, HIGH); // Right motor forward
      digitalWrite(RMN, LOW);
      Serial.println("Moving Forward");
    } 
    else if (LSD == 1 && RSD == 0) // If left sensor is on the black line (1), turn left
    { 
      // Turns Left
      analogWrite(ENA, 150); // Speed control for left motor
      analogWrite(ENB, 150); // Speed control for right motor
      digitalWrite(LMP, LOW); // Left motor stop
      digitalWrite(LMN, HIGH); // Left motor reverse
      digitalWrite(RMP, HIGH); // Right motor forward
      digitalWrite(RMN, LOW);
      Serial.println("Turning Left");
    }
    else if (LSD == 0 && RSD == 1) // If right sensor is on the black line (1), turn right
    {
      // Turns Right
      analogWrite(ENA, 150); // Speed control for left motor
      analogWrite(ENB, 150); // Speed control for right motor
      digitalWrite(LMP, HIGH); // Left motor forward
      digitalWrite(LMN, LOW);
      digitalWrite(RMP, LOW); // Right motor stop
      digitalWrite(RMN, HIGH); // Right motor reverse
      Serial.println("Turning Right");
    }
  }  
  else if (distance < 15) // If the distance < 15 cm, stop the robot
  {
    // Stop the robot
    analogWrite(ENA, 0); // Stop left motor
    analogWrite(ENB, 0); // Stop right motor
    digitalWrite(LMP, LOW);
    digitalWrite(LMN, LOW);
    digitalWrite(RMP, LOW);
    digitalWrite(RMN, LOW);
    Serial.println("Obstacle Detected: Stopping");
  }
}
